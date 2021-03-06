/*
Copyright 2017 Google Inc. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS-IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "lullaby/systems/render/detail/sort_order.h"

#include "lullaby/systems/transform/transform_system.h"

namespace lull {
namespace detail {
namespace {

// Ensures the offset is within the valid range, logging if it's not.
RenderSortOrderOffset CheckOffsetBounds(EntityIdPair entity_id_pair,
                                        RenderSortOrderOffset offset) {
  if (offset >= lull::RenderSortOrder::kMaxOffset) {
    LOG(INFO) << "Offset exceeds valid range for entity "
              << entity_id_pair.entity << " with id " << entity_id_pair.id
              << "! "
              << "Resetting to max offset.";
    return lull::RenderSortOrder::kMaxOffset;
  }
  if (offset <= -lull::RenderSortOrder::kMaxOffset) {
    LOG(INFO) << "Offset exceeds valid range for entity "
              << entity_id_pair.entity << " with id " << entity_id_pair.id
              << "! "
              << "Resetting to min offset.";
    return -lull::RenderSortOrder::kMaxOffset;
  }
  return offset;
}

// Calculates the sort order from an offset and a depth.
RenderSortOrder SortOrderFromOffset(RenderSortOrderOffset offset, int depth) {
  const int shift = lull::RenderSortOrder::kRootShift -
                    lull::RenderSortOrder::kNumBitsPerGroup * depth;
  return (static_cast<RenderSortOrder>(offset) << shift);
}

}  // namespace

constexpr RenderSortOrderOffset SortOrderManager::kUseDefaultOffset;

void SortOrderManager::Destroy(EntityIdPair entity_id_pair) {
  requested_offset_map_.erase(entity_id_pair);
  root_offset_map_.erase(entity_id_pair);
}

RenderSortOrderOffset SortOrderManager::GetOffset(
    EntityIdPair entity_id_pair) const {
  const auto iter = requested_offset_map_.find(entity_id_pair);
  return (iter != requested_offset_map_.end() ? iter->second
                                              : kUseDefaultOffset);
}

void SortOrderManager::SetOffset(EntityIdPair entity_id_pair,
                                 RenderSortOrderOffset offset) {
  requested_offset_map_[entity_id_pair] = offset;
}

RenderSortOrderOffset SortOrderManager::CalculateSiblingOffset(
    EntityIdPair entity_id_pair, Entity parent) const {
  DCHECK_NE(parent, kNullEntity);

  RenderSortOrderOffset offset = 1;

  const auto* transform_system = registry_->Get<TransformSystem>();
  const std::vector<Entity>* siblings = transform_system->GetChildren(parent);
  if (!siblings || siblings->empty()) {
    LOG(DFATAL) << "The parent of an Entity must have at least one child!";
    return offset;
  }

  for (Entity sibling : *siblings) {
    if (sibling == entity_id_pair.entity) {
      // Prevent the offset of the entity_id_pair from going over the max valid
      // value so we don't log the calculated offset as an error in
      // CheckOffsetBounds.
      return std::min(lull::RenderSortOrder::kMaxOffset - 1, offset);
    }
    ++offset;
  }

  LOG(DFATAL) << "The parent of an Entity must have at least one child that "
                 "is the Entity itself!";
  return offset;
}

RenderSortOrder SortOrderManager::CalculateRootSortOrder(
    EntityIdPair entity_id_pair) {
  auto req = requested_offset_map_.find(entity_id_pair);
  RenderSortOrderOffset offset;

  if (req != requested_offset_map_.end() && req->second != kUseDefaultOffset) {
    offset = req->second;
  } else {
    // Use the assigned root level offset, adding one if necessary.
    auto result = root_offset_map_.emplace(entity_id_pair, next_root_offset_);
    const bool added = result.second;

    if (added && ++next_root_offset_ >= lull::RenderSortOrder::kMaxOffset) {
      next_root_offset_ = 1;
    }

    const auto root = result.first;
    offset = root->second;
  }

  return SortOrderFromOffset(offset, /* depth = */ 0);
}

std::pair<RenderSortOrder, int> SortOrderManager::CalculateSortOrderAndDepth(
    EntityIdPair entity_id_pair) {
  const auto* transform_system = registry_->Get<TransformSystem>();
  const Entity parent = transform_system->GetParent(entity_id_pair.entity);

  if (parent == kNullEntity) {
    return std::make_pair(CalculateRootSortOrder(entity_id_pair), 0);
  }

  auto iter = requested_offset_map_.find(entity_id_pair);
  RenderSortOrderOffset offset;
  if (iter == requested_offset_map_.end() ||
      iter->second == kUseDefaultOffset) {
    offset = CalculateSiblingOffset(entity_id_pair, parent);
  } else {
    offset = iter->second;
  }

  offset = CheckOffsetBounds(entity_id_pair, offset);

  const auto parent_order_depth_pair =
      CalculateSortOrderAndDepth(EntityIdPair(parent, entity_id_pair.id));
  RenderSortOrder parent_sort_order = parent_order_depth_pair.first;
  const int parent_depth = parent_order_depth_pair.second;

  const int depth = parent_depth + 1;
  if (depth >= lull::RenderSortOrder::kMaxDepth) {
    LOG(DFATAL) << "Cannot exceed max depth.";
  }

  if (offset < 0) {
    // For negative offsets, subtract 1 from the parent's sort order within
    // the parent's sort order block.
    parent_sort_order -= SortOrderFromOffset(1, parent_depth);

    // For negative offsets, start at the highest possible value and work
    // backwards.  This will be offset by the fact that the parent block
    // offset has been reduced by 1.
    offset += lull::RenderSortOrder::kMaxOffset;
  }

  return std::make_pair(parent_sort_order + SortOrderFromOffset(offset, depth),
                        depth);
}

RenderSortOrder SortOrderManager::CalculateSortOrder(
    EntityIdPair entity_id_pair) {
  const auto order_depth_pair = CalculateSortOrderAndDepth(entity_id_pair);
  return order_depth_pair.first;
}

}  // namespace detail
}  // namespace lull
