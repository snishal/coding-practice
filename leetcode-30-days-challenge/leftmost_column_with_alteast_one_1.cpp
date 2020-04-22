/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int x, int y);
 *     vector<int> dimensions();
 * };
 */

class Solution {
public:
    int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
        vector<int> dimensions = binaryMatrix.dimensions();
        int r = 0, c = dimensions[1] - 1, lCol = -1;
        
        while(r < dimensions[0] && c >= 0){
            if(binaryMatrix.get(r, c) == 1){
                lCol = c;
                c--;
            }else{
                r++;
            }
        }
        
        return lCol;
    }
};