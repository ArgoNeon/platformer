#include <iostream>
#include <fstream>
 
int main() {
	char c0 = '0';
	char cg = 'g';
	std::ofstream map;
   	map.open("sample.dat");
   	if (map.is_open()) {
		for (int i = 0; i < 45; i++) {
			for (int j = 0; j < 400; j++)
				map << c0;
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
