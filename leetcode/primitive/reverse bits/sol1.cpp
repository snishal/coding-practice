#define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64 
#define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16) 
#define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 ) 

class Solution {
private:
    unsigned int lookuptable[256] = { R6(0), R6(2), R6(1), R6(3) }; 
public:
    uint32_t reverseBits(uint32_t n) {
        const int kWordSize = 8;
        const int kBitMask = 0xFF;
        
        return lookuptable[n & kBitMask] << 3 * kWordSize |
                lookuptable[(n >> kWordSize) & kBitMask] << 2 * kWordSize |
                lookuptable[(n >> 2 * kWordSize) & kBitMask] << kWordSize |
                lookuptable[(n >> 3 * kWordSize) & kBitMask];
    }  
};