#include <iostream>
#include <fstream>
#include <chrono>

#include <divsufsort.h>

using namespace std;
using namespace std::chrono;


int lcp(unsigned char *T1,unsigned char *T2, int n){
    int i = 0;
    while (T1[i+n] == T2[i+n]){
        i++;
    }
    return i+n;
}


int makeLCP(int *SA, int *LCP,int *SAi, int *maxLCPi, int n, unsigned char *T){

    //Time for constructing SAi
    auto start = high_resolution_clock::now();
    for (int i = 0; i < n; i++){
        SAi[SA[i]] = i;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    auto start2 = high_resolution_clock::now();
    
    int k = 0;
    LCP[0] = 0;
    
    int maxLCP = -1;
    int maxCount = 0;

    k = LCP[SAi[0]];

    for (int i = 0; i < n; i++){
        if (SAi[i] == 0){
            LCP[SAi[i]] = 0;
            continue;
        }
        //const char *T1 = T + i;
        //const char *T2 = T + SA[SAi[i]-1];
        k = k - 1;
        if (k < 0){
            k = 0;
        }

        LCP[SAi[i]] = lcp(T + i, T + SA[SAi[i]-1], k);

        //cout<<maxLCP<<endl;

        if (LCP[SAi[i]] > maxLCP){
            maxCount = 2;
            maxLCP = LCP[SAi[i]];
            maxLCPi[0] = SAi[i]-1;
            maxLCPi[1] = SAi[i];
        }
        else if (LCP[SAi[i]] == maxLCP){
            maxLCPi[maxCount] = SAi[i];
            maxCount++;
        }
        k = LCP[SAi[i]];
    }

    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);

    cout << "Time taken to construct SAi: " << duration.count() << " microseconds" << endl;
    cout << "Time taken to construct LCP: " << duration2.count() << " microseconds" << endl;
    
    return maxCount;
}

int main(int argc, char **argv ){
    //std::cout << argc << std::endl;
	if( argc <= 1 ){
		std::cerr << "Usage: "<<argv[0]<<" [infile] [-r/--random]" << std::endl;

        std::cerr << "infile: The file containing the sequence to be sorted" << std::endl;
        std::cerr << "-r/--random: If present, the program will generate a random sequence of length 10^6" << std::endl;

        std::cerr << "Inputs are" << std::endl;
        for (int i = 0; i < argc; i++){
            std::cerr << argv[i] << std::endl;
        }

		return -1;
	}

	std::ifstream input(argv[1]);
	if(!input.good()){
		std::cerr << "Error opening '"<<argv[1]<<"'. Bailing out." << std::endl;
		return -1;
	}

    bool verbose = false;
    if (argc > 2){
        if (std::string(argv[2]) == "-v" || std::string(argv[2]) == "--verbose"){
            std::cout << "Verbose mode enabled" << std::endl;
            verbose = true;
        }
    }

    std::string line, name, content;
	while( std::getline( input, line ).good() ){
        //std::cout << line << std::endl;
		if( line.empty() || line[0] == '>' ){ // Identifier marker
			if( !name.empty() ){ // Print out what we read from the last entry
				//std::cout << name << std::endl;
				name.clear();
			}
			if( !line.empty() ){
				name = line.substr(1);
			}
			content.clear();
		} else if( !name.empty() ){
			if( line.find(' ') != std::string::npos ){ // Invalid sequence--no spaces allowed
				name.clear();
				content.clear();
			} else {
				content += line;
			}
		}
	}

    //cout<< "Sequence Imported" << endl;

    cout<< "String Length: " << content.size() <<endl;

    int n = content.size();

    // allocate
    int *SA = (int *)malloc(n * sizeof(int));

    // sort
    unsigned char *T = (unsigned char *)malloc(n * sizeof(unsigned char));
    for (int i = 0; i < n; i++){
        T[i] = content[i];
    }

    auto start = high_resolution_clock::now();
    divsufsort((unsigned char *)T, SA, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken to construct SA: " << duration.count() << " microseconds" << endl;

    printf("SA built successfully\n");
    // LCP
    int *LCP;
    LCP = (int *)malloc(n * sizeof(int));
    int *SAi = (int *)malloc(n * sizeof(int));
    int *maxLCPi = (int *)malloc(n * sizeof(int));

    int repeatCount = makeLCP(SA, LCP, SAi, maxLCPi, n, T);

    printf("Indexs of longest repeating string:\n");
    
    for (int i = 0; i < repeatCount; i++){
        printf("%d\n", SA[maxLCPi[i]]);
    }

    printf("Length of longest repeating string: %d\n", LCP[maxLCPi[1]]);

    if (verbose){
        cout<< "String: " << T <<endl;
        //output
        for(int i = 0; i < n; ++i) {
            printf("SA[%2d] = %2d\tLCP[%2d] = %2d\t: ", i, SA[i], i, LCP[i]);
            cout << (content+'$').substr(SA[i]) << endl;
        }
        
    }

    // deallocate
    free(SA);
    free(SAi);
    free(maxLCPi);

    return 0;
}
