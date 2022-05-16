#include <iostream>
#include <fstream>
 
int main() {
	char c0 = '0';
	char cg = 'g';
	std::ofstream map;
   	map.open("sample.dat");
   	if (map.is_open()) {

		for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 400; j++)
                                map << cg;
                map << std::endl;
                }

		for (int i = 5; i < 45; i++) {
			map << cg;
			for (int j = 1; j < 399; j++)
				map << c0;
			map << cg;
			map << std::endl;
		}

		for (int i = 45; i < 50; i++) {
                        for (int j = 0; j < 400; j++)
                                map << cg;
                map << std::endl;
                }
    	}
     	
	map.close();	
    	return 0;
}
