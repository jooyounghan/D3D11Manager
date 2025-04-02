#include "GraphicsPSOObject.h"

#include "VertexShader.h"
#include "HullShader.h"
#include "DomainShader.h"
#include "GeometryShader.h"
#include "PixelShader.h"
#include "RasterizerState.h"
#include "BlendState.h"
#include "DepthStencilState.h"
#include "SamplerState.h"

#include <vector>

using namespace std;
using namespace D3D11;

CGraphicsPSOObject::CGraphicsPSOObject(
	CVertexShader* vertexShader,
	CHullShader* hullShader,
	CDomainShader* domainShader,
	CGeometryShader* geometryShader,
	CPixelShader* pixelShader,
	ID3D11RasterizerState* rasterizerState,
	ID3D11BlendState* blendState,
	ID3D11DepthStencilState* depthStencilState,
	ID3D11SamplerState* const* samplerStates,
	UINT samplerStateCount
) noexcept
	: 	m_rasterizerState(rasterizerState),
	m_blendState(blendState),
	m_depthStencilState(depthStencilState),
	m_samplerStates(samplerStates),
	m_samplerStateCount(samplerStateCount)
{
	m_shaders[0] = vertexShader;
	m_shaders[1] = hullShader;
	m_shaders[2] = domainShader;
	m_shaders[3] = geometryShader;
	m_shaders[4] = pixelShader;
}

void CGraphicsPSOObject::ApplyPSO(
	ID3D11DeviceContext* deviceContext,
	const FLOAT blendFactor[4],
	UINT blendSamplerMask,
	UINT stencilRef
)
{
	for (auto& shaders : m_shaders)
	{
		if (shaders)
		{
			shaders->SetShader(deviceContext);
			shaders->SetSamplerState(deviceContext, m_samplerStates, m_samplerStateCount);
		}
	}

	if (m_rasterizerState) deviceContext->RSSetState(m_rasterizerState);
	if (m_blendState) deviceContext->OMSetBlendState(m_blendState, blendFactor, blendSamplerMask);
	if (m_depthStencilState) deviceContext->OMSetDepthStencilState(m_depthStencilState, stencilRef);
}
