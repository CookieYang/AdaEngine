#include "RenderPineline.h"
#include "ForwardPineline.h"
RenderPineline* RenderPineline::createPineline(PinelineType type) {
	switch (type)
	{
	case FORWARD:
		return new ForwardPineline;
		break;
	case DEFER:
		break;
	case CARTOON:
		break;
	default:
		break;
	}
}
