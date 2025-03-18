#pragma once

#ifndef GRAPHICSPSOOBJEC_H
#define GRAPHICSPSOOBJEC_H

#include "D3D11DllHelper.h"

#include <d3d11.h>
#include <wrl/client.h>

#include "VertexShader.h"
#include "HullShader.h"
#include "DomainShader.h"
#include "GeometryShader.h"
#include "PixelShader.h"

namespace D3D11
{
	class CGraphicsPSOObject
	{
	public:
		CGraphicsPSOObject(
			CVertexShader* vertexShader,
			CHullShader* hullShader,
			CDomainShader* domainShader,
			CGeometryShader* geometryShader,
			CPixelShader* pixelShader,
			ID3D11RasterizerState* rasterizerState,
			ID3D11BlendState* blendState,
			ID3D11DepthStencilState* depthStencilState
		);
	};
}
#endif