#pragma once

#include "Core/output.h"
#include "CLW.h"
#include "multiple_view.h"

namespace Baikal
{
    class ClwOutput : public Output
    {
    public:
        ClwOutput(std::uint32_t w, std::uint32_t h, CLWContext context)
        : Output(w, h)
        , m_context(context)
        , m_data(context.CreateBuffer<RadeonRays::float3>(w*h, CL_MEM_READ_WRITE))
        {
        }

        void GetData(RadeonRays::float3* data) const
        {
            m_context.ReadBuffer(0, m_data, data, m_data.GetElementCount()).Wait();
        }

        void Clear(RadeonRays::float3 const& val)
        {
            m_context.FillBuffer(0, m_data, val, m_data.GetElementCount()).Wait();
        }

        CLWBuffer<RadeonRays::float3> data() const { return m_data; }

    private:
        CLWBuffer<RadeonRays::float3> m_data;
        CLWContext m_context;
    };

	// COVART: multiple view
	class ClwMultipleOutput : public Output
	{
	public:
		ClwMultipleOutput(std::uint32_t w, std::uint32_t h, CLWContext context, size_t segment_count = MULTIPLE_VIEW_SIZE)
			: Output(w, h)
			, m_context(context)
			, m_data(context.CreateBuffer<RadeonRays::float3>(w * h* segment_count, CL_MEM_READ_WRITE))
		{
		}

		void GetData(RadeonRays::float3* data) const
		{
			m_context.ReadBuffer(0, m_data, data, m_data.GetElementCount()).Wait();
		}

		void Clear(RadeonRays::float3 const& val)
		{
			m_context.FillBuffer(0, m_data, val, m_data.GetElementCount()).Wait();
		}

		CLWBuffer<RadeonRays::float3> data() const { return m_data; }

	private:
		CLWBuffer<RadeonRays::float3> m_data;
		CLWContext m_context;
	};


	// KAOCC: pipeline buffer
	//class ClwPipelineOutput : public Output
	//{
	//public:
	//	ClwPipelineOutput(std::uint32_t w, std::uint32_t h, CLWContext context)
	//		: Output(w, h)
	//		, m_context(context)
	//		, m_data(context.CreateBuffer<RadeonRays::float3>(w * h * IMAGE_COUNT * BOUNCE_COUNT, CL_MEM_READ_WRITE))
	//	{
	//	}

	//	void GetData(RadeonRays::float3* data) const
	//	{
	//		m_context.ReadBuffer(0, m_data, data, m_data.GetElementCount()).Wait();
	//	}

	//	void Clear(RadeonRays::float3 const& val)
	//	{
	//		m_context.FillBuffer(0, m_data, val, m_data.GetElementCount()).Wait();
	//	}

	//	CLWBuffer<RadeonRays::float3> data() const { return m_data; }

	//private:
	//	CLWBuffer<RadeonRays::float3> m_data;
	//	CLWContext m_context;

	//public:
	//	static const unsigned IMAGE_COUNT = 1;
	//	static const unsigned BOUNCE_COUNT = 5;
	//};



}
