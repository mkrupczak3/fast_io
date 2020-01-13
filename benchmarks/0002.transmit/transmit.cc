#include"../timer.h"
#include"../../include/fast_io.h"
#include"../../include/fast_io_device.h"
#include"../../include/fast_io_legacy.h"
#include<fstream>

int main()
try
{
	{
		fast_io::timer tm("fast_io ofstream <= ifstream");
		std::ifstream ifst("large_file.txt",std::ifstream::binary);
		std::ofstream ofst("large_file_stream.txt",std::ofstream::binary);
		ofst<<ifst.rdbuf();
	}
	{
		fast_io::timer tm("fast_io obuf_file <= ibuf_file");
		fast_io::ibuf_file ib("large_file.txt");
		fast_io::obuf_file ob("large_file_fast_io.txt");
		transmit(ob,ib);
	}

}
catch(std::exception const& e)
{
	println(fast_io::err,e);
}
