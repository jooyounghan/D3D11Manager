#include "GraphicsPSOObject.h"

using namespace D3D11;

//CGraphicsPSOObject::CGraphicsPSOObject()
//{
//	ID3D11DeviceContext* deviceContext;
//	deviceContext->IASetVertexBuffers;
//	deviceContext->IASetIndexBuffer;
//	deviceContext->IASetPrimitiveTopology;
//	deviceContext->IASetInputLayout;
//
//	deviceContext->VSSetShader;
//	deviceContext->VSSetConstantBuffers;
//	deviceContext->VSSetShaderResources;
//	deviceContext->VSSetSamplers;
//
//	deviceContext->HSSetShader;
//	deviceContext->HSSetConstantBuffers;
//	deviceContext->HSSetShaderResources;
//	deviceContext->HSSetSamplers;
//
//	deviceContext->DSSetShader;
//	deviceContext->DSSetConstantBuffers;
//	deviceContext->DSSetShaderResources;
//	deviceContext->DSSetSamplers;
//
//	deviceContext->GSSetShader;
//	deviceContext->GSSetConstantBuffers;
//	deviceContext->GSSetShaderResources;
//	deviceContext->GSSetSamplers;
//	
//	deviceContext->RSSetScissorRects;
//	deviceContext->RSSetState;
//	deviceContext->RSSetViewports;
//
//	deviceContext->PSSetShader;
//	deviceContext->PSSetConstantBuffers;
//	deviceContext->PSSetShaderResources;
//	deviceContext->PSSetSamplers;
//
//	deviceContext->OMSetBlendState;
//	deviceContext->OMSetDepthStencilState;
//	deviceContext->OMSetRenderTargets;
//}

CGraphicsPSOObject::CGraphicsPSOObject(
	CVertexShader* vertexShader, 
	CHullShader* hullShader,
	CDomainShader* domainShader, 
	CGeometryShader* geometryShader, 
	CPixelShader* pixelShader,
	ID3D11RasterizerState* rasterizerState,
	ID3D11BlendState* blendState, 
	ID3D11DepthStencilState* depthStencilState
)
{
	ID3D11DeviceContext* deviceContext;
	ID3D11Device* device;

}
