#pragma once

#include <vector>
#include <hash_map>
#include <string>

#include <DirectXMath.h>
//#include <DirectXMathVector.inl>
//#include <DirectXMathConvert.inl>

namespace OSO
{
    typedef std::wstring OString;

    typedef DirectX::XMFLOAT3 XMFLOAT3;
    typedef DirectX::XMFLOAT4 XMFLOAT4;
    typedef DirectX::XMFLOAT4X4 XMFLOAT4X4;
    typedef DirectX::XMMATRIX XMMATRIX;
    typedef DirectX::XMVECTOR XMVECTOR;

    using DirectX::XMVector3Normalize;
    using DirectX::XMStoreFloat3;
    using DirectX::XMVector3Cross;
    using DirectX::XMVectorGetX;
    using DirectX::XMVector3Dot;

    //typedef DirectX::XMVectorSubtract XMVectorSubtract;
    //typedef DirectX::XMVector3Normalize XMVector3Normalize;
    //typedef DirectX::XMVector3Cross XMVector3Cross;
  
    //typedef DirectX::XMStoreFloat3 XMStoreFloat3;

}


