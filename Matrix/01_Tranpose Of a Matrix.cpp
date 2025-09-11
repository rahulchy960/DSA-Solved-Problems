class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>>ans(m, vector<int>(n)); // vector by interchanging row and cols for transpose
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++)
                ans[i][j] = matrix[j][i];
        }
        return ans;
    }
};



vector<vector<int>> transpose(vector<vector<int>>& matrix) { // valid only if square matrix
    int n = matrix.size();
    int m = matrix[0].size();
    for(int i=0;i<m;i++){
        for(int j=i+1;j<n;j++)
            swap(matrix[i][j], matrix[j][i]);
    }
    return matrix;
}
