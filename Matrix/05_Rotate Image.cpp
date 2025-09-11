class Solution {  // 48. Rotate Image
public:
    void rotate(vector<vector<int>>& matrix) {  // right rotate
        int n = matrix.size();
        vector<vector<int>>temp(n, vector<int>(n));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                temp[j][n-1-i] = matrix[i][j];
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                matrix[i][j] = temp[i][j];
            }
        }
    }
};

void rotate(vector<vector<int>>& matrix) {  // right rotate in place
        int n = matrix[0].size();
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                swap(matrix[i][j], matrix[j][i]);  // transpose
            }
        }
        for(int i=0;i<n;i++)
            reverse(matrix[i].begin(), matrix[i].end());  // horizontal reverse
}

class Solution {   // 48. Rotate Image in-place
public:
    
    void rotate(vector<vector<int>>& matrix) {  // left rotate
        int n = matrix[0].size();
        for(int i=0;i<n;i++){  // vertical reverse
            int top = 0, bot = n-1;
            while(top<=bot){
                swap(matrix[top][i], matrix[bot][i]);
                top++;
                bot--;
            }
        }
        for(int i=0;i<n;i++){   // transpose
            for(int j=i+1;j<n;j++){
                swap(matrix[i][j], matrix[j][i]);
            }
        }
    }
};