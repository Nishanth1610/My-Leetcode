class Solution {
public:
    int maxBottlesDrunk(int numB, int numE) {
     int ans=numB;
     while(numB>=numE){
        numB-=numE;
        ans++;
        numE++;
        numB++;
     }   
     return ans;
    }
};