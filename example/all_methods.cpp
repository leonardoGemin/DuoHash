// Compile with  g++-13 -std=c++0x -O3 -fopenmp -I../include -L../build -o allMethods allMethods.cpp -lDuoHash

#include <DuoHash.h>
#include <chrono>
#include <iomanip>


int main()
{
	std::string dataset = "./TestInputFile/small_test.txt";
	std::vector<std::string> sequences;
	if (!loadFile(dataset, sequences))
		std::exit(1);

	std::string seedset = "./Seeds/W22L31.fna";
	std::vector<SpacedQmer> multi_spaced;
	{
		std::vector<std::string> tmp;
		if (!loadFile(seedset, tmp))
			std::exit(1);

		multi_spaced.reserve(tmp.size());
		for (auto seed : tmp)
			multi_spaced.emplace_back(SpacedQmer(seed, 0));
	}



	std::cerr << "\nTest with single seed\n";
	DuoHash test(sequences, multi_spaced[0]);

	{
		std::cerr << "GetEncoding_naive... ";
		std::vector<Hash_V> hashes;

		auto t1 = std::chrono::steady_clock::now();
		test.GetEncoding_naive(hashes, getBoth);
		auto t2 = std::chrono::steady_clock::now();
		
		auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";
	}

	{
		std::cerr << "GetEncoding_FSH... ";
		std::vector<Hash_V> hashes;

		auto t1 = std::chrono::steady_clock::now();
		test.GetEncoding_FSH(hashes, getBoth);
		auto t2 = std::chrono::steady_clock::now();
		
		auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";
	}

	{
		std::cerr << "GetEncoding_ISSH... ";
		std::vector<Hash_V> hashes;

		auto t1 = std::chrono::steady_clock::now();
		test.GetEncoding_ISSH(hashes, getBoth);
		auto t2 = std::chrono::steady_clock::now();
		
		auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";



		std::cerr << "PrintFASTA... ";

		t1 = std::chrono::steady_clock::now();
		test.PrintFASTA(hashes);
		t2 = std::chrono::steady_clock::now();

		t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";
	}


	
	std::cerr << "\nTest with multiple seed\n";
	DuoHash_multi test_multi(sequences, multi_spaced);

	{
		std::cerr << "GetEncoding_naive... ";
		std::vector<Hash_V_V> hashes;

		auto t1 = std::chrono::steady_clock::now();
		test_multi.GetEncoding_naive(hashes);
		auto t2 = std::chrono::steady_clock::now();
		
		auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";
	}

	{
		std::cerr << "GetEncoding_FSH... ";
		std::vector<Hash_V_V> hashes;

		auto t1 = std::chrono::steady_clock::now();
		test_multi.GetEncoding_FSH(hashes);
		auto t2 = std::chrono::steady_clock::now();
		
		auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";
	}

	{
		std::cerr << "GetEncoding_ISSH... ";
		std::vector<Hash_V_V> hashes;

		auto t1 = std::chrono::steady_clock::now();
		test_multi.GetEncoding_ISSH(hashes);
		auto t2 = std::chrono::steady_clock::now();
		
		auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";
	}


	{
		std::cerr << "GetEncoding_FSH_multi... ";
		std::vector<Hash_V_V> hashes;

		auto t1 = std::chrono::steady_clock::now();
		test_multi.GetEncoding_FSH_multi(hashes);
		auto t2 = std::chrono::steady_clock::now();
		
		auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";
	}

	{
		std::cerr << "GetEncoding_MISSH_v1... ";
		std::vector<Hash_V_V> hashes;

		auto t1 = std::chrono::steady_clock::now();
		test_multi.GetEncoding_MISSH_v1(hashes, getBoth);
		auto t2 = std::chrono::steady_clock::now();
		
		auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";



		std::cerr << "PrintFASTA... ";

		t1 = std::chrono::steady_clock::now();
		test_multi.PrintFASTA(hashes, "out");
		t2 = std::chrono::steady_clock::now();

		t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";
	}

	{
		std::cerr << "GetEncoding_MISSH_col... ";
		std::vector<Hash_V_V> hashes;

		auto t1 = std::chrono::steady_clock::now();
		test_multi.GetEncoding_MISSH_col(hashes);
		auto t2 = std::chrono::steady_clock::now();
		
		auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";
	}

	{
		std::cerr << "GetEncoding_MISSH_col_parallel... ";
		std::vector<Hash_V_V> hashes;

		auto t1 = std::chrono::steady_clock::now();
		test_multi.GetEncoding_MISSH_col_parallel(hashes);
		auto t2 = std::chrono::steady_clock::now();
		
		auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";
	}

	{
		std::cerr << "GetEncoding_MISSH_row... ";
		std::vector<Hash_V_V> hashes;

		auto t1 = std::chrono::steady_clock::now();
		test_multi.GetEncoding_MISSH_row(hashes);
		auto t2 = std::chrono::steady_clock::now();
		
		auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";
	}
}