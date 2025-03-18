
#include <array>
#include <string>


class myUUID {
	std::array<uint8_t, 16> uuidArray = {0}; //chose array for fixed size
	void setUUID(const void* binaryData);
 
public:
	myUUID();
	~myUUID();

	
	std::array<uint8_t, 16>& getUUID() ;
	std::string getBinary() ;
		
};