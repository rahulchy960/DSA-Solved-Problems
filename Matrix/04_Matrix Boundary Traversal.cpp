class Solution {
  public:
    vector<int> boundaryTraversal(vector<vector<int>>& mat) {
        // code here
        int m = mat.size();
        int n = mat[0].size();
        vector<int>res;
        if(m==1){
            for(int i=0;i<n;i++)
                res.push_back(mat[0][i]);
        } else if(n==1){
            for(int i=0;i<n;i++)
                res.push_back(mat[i][0]);
        } else {
            for(int j=0;j<n;j++)
                res.push_back(mat[0][j]);
            for(int i=1;i<m;i++)
                res.push_back(mat[i][n-1]);
            for(int j=n-2;j>=0;j--)
                res.push_back(mat[m-1][j]);
            for(int i=m-2;i>=1;i--)
                res.push_back(mat[i][0]);
            
        }
        return res;
    }
};
