#include "stdafx.h"
#include "math_ext.h"

using namespace std;

static const float to_rads = 3.141592653589793238463f / 180.0f;

float math_ext::toRads(const float angle_deg)
{
	return angle_deg * to_rads;
}