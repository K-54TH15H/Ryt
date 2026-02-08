#ifndef BVH_HPP
#define BVH_HPP

#include <ryt/core/aabb.hpp>
#include <ryt/core/hitrecord.hpp>

namespace RYT {
struct RaytracingContext; // Forward Declaration

// ********** BVHNode ********* //
struct BVHNode {
  AABB bBox;
  int leftIndex;
  int rightIndex;
  bool isLeaf;

  BVHNode() : leftIndex(-1), rightIndex(-1), isLeaf(false) {}
};

int ConstructBVHTree(RaytracingContext *context, size_t start, size_t end);
bool HitBVH(const RaytracingContext *context, int nodeIndex, const Ray &r,
            Interval rayT, HitRecord &rec);
} // namespace RYT
#endif
