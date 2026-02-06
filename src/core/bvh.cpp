#include <ryt/rtcore.hpp>
#include <algorithm>

namespace RYT
{
    static bool BoxCompare(const Hittable& a, const Hittable& b, int axisIndex)
    {
	Interval aAxisInterval = (a.bBox).AxisInterval(axisIndex);
	Interval bAxisInterval = (b.bBox).AxisInterval(axisIndex);
	return aAxisInterval.min < bAxisInterval.min;
    }
    static bool BoxXCompare(const Hittable& a, const Hittable& b){ return BoxCompare(a, b, 0); }
    static bool BoxYCompare(const Hittable& a, const Hittable& b){ return BoxCompare(a, b, 1); }
    static bool BoxZCompare(const Hittable& a, const Hittable& b){ return BoxCompare(a, b, 2); }

    int ConstructBVHTree(RaytracingContext* context, size_t start, size_t end)
    {
	size_t span = end - start;
	int  axis = RandomInt(0, 2);
	auto comparator = (axis == 0) ? BoxXCompare : (axis == 1) ? BoxYCompare : BoxZCompare;

	int currentIndex = context->bvhNodeSize++;
	BVHNode* node = &context->bvhNodes[currentIndex];

	if(span == 1)
	{
	    node->isLeaf = true;
	    node->leftIndex = (int) start;
	    node->bBox = context->hittables[start].bBox;
	    
	    return currentIndex;
	}

	// Need to check comparator
	std::sort(context->hittables + start, context->hittables + end, comparator);
	
	size_t mid = start + span/2;
	
	int left = ConstructBVHTree(context, start, mid);
	int right = ConstructBVHTree(context, mid, end);
    
	node->isLeaf = false;
	node->leftIndex = left;
	node->rightIndex = right;
	node->bBox = AABB(context->bvhNodes[left].bBox, context->bvhNodes[right].bBox);

	return currentIndex;
    }

    bool HitBVH(const RaytracingContext* context, int nodeIndex, const Ray& r, Interval rayT, HitRecord& rec)
    {
	const BVHNode& node = context->bvhNodes[nodeIndex];

	if(!node.bBox.Hit(r, rayT)) return false;

	if(node.isLeaf)
	{
	    return context->hittables[node.leftIndex].Hit(r, rayT, rec);
	}
	else
	{
	    bool hitLeft = HitBVH(context, node.leftIndex, r, rayT, rec);

	    Interval newRange = hitLeft ? Interval(rayT.min, rec.t) : rayT;
	    bool hitRight = HitBVH(context, node.rightIndex, r, newRange, rec);

	    return ( hitLeft || hitRight );
	}
    }
}
