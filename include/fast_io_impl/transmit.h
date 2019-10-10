#pragma once

namespace fast_io
{

template<output_stream output,input_stream input>
inline std::uint_least64_t bufferred_transmit(output& outp,input& inp)
{
	std::uint_least64_t transmitted_bytes(0);
	for(std::array<unsigned char,65536> array;;)
	{
		auto p(inp.read(array.data(),array.data()+array.size()));
		std::uint_least64_t transmitted_this_round(p-array.data());
		transmitted_bytes+=transmitted_this_round;
		outp.write(array.data(),p);
		if(transmitted_this_round!=array.size())
			return transmitted_bytes;
	}
}

template<output_stream output,input_stream input>
inline std::uint_least64_t bufferred_transmit(output& outp,input& inp,std::uint_least64_t bytes)
{
	std::uint_least64_t transmitted_bytes(0);
	for(std::array<unsigned char,65536> array;bytes;)
	{
		std::uint_least64_t b(array.size());
		if(bytes<b)
			b=bytes;
		auto p(inp.read(array.data(),array.data()+b));
		std::uint_least64_t read_bytes(p-array.data());
		outp.write(array.data(),p);
		transmitted_bytes+=read_bytes;
		if(read_bytes!=b)
			return transmitted_bytes;
		bytes-=read_bytes;
	}
	return transmitted_bytes;
}

template<output_stream output,input_stream input,typename... Args>
inline auto transmit(output& outp,input& inp,Args&& ...args)
{
	if constexpr(zero_copy_output_stream<output>&&zero_copy_input_stream<input>)
		return zero_copy_transmit(outp,inp,std::forward<Args>(args)...);
	else
		return bufferred_transmit(outp,inp,std::forward<Args>(args)...);
}

}