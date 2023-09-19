#include<bits/stdc++.h>
#define ll long long
#define N 300005

using namespace std;
int T,n,m; string s;
ll dp[2][63][8],sum[8]; const int P=998244353;
int check(char ch) {
    if (ch>='0' && ch<='9') return 0;
    else if (ch>='A' && ch<='Z') return 1;
    else if (ch>='a' && ch<='z') return 2;
    else return 3;
}
int a(char ch) {
    int k=check(ch);
    if (k==0) return ch-48;
    if (k==1) return ch-55;
    if (k==2) return ch-61;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>s;
    dp[1][62][0]=1;
    int id; sum[0]=1;
    for (int i=0,opt;i<n;i++) {
        opt=check(s[i]); 
        char ch=s[i];
        id=i%2;
        
        if (opt==0) {
            for (int k=(i!=0);k<8;k++) {
                for (int j=0;j<62+(i==0);j++)
                if (dp[id^1][j][k]>=0 && a(ch)!=j) 
                    (dp[id][a(ch)][k|1]+=dp[id^1][j][k])%=P;
            }
        }
        if (opt==1) {
            for (int k=(i!=0);k<8;k++) {
                for (int j=0;j<62+(i==0);j++)
                if (dp[id^1][j][k]>=0 && a(ch)!=j) 
                    (dp[id][a(ch)][k|2]+=dp[id^1][j][k])%=P;
            }
        }
        if (opt==2) {
            for (int k=(i!=0);k<8;k++) {
                for (int j=0;j<62+(i==0);j++)
                if (dp[id^1][j][k]>=0 && a(ch)!=j) 
                    (dp[id][a(ch)][k|4]+=dp[id^1][j][k])%=P;
            }
            for (int k=(i!=0);k<8;k++) {
                for (int j=0;j<62+(i==0);j++)
                if (dp[id^1][j][k]>=0 && a(ch)-26!=j) 
                    (dp[id][a(ch)-26][k|2]+=dp[id^1][j][k])%=P;
            }
        }
        if (opt==3) {
            for (int k=(i!=0);k<8;k++) {
                for (int j=0,t;j<62;j++) {
                    if (j<=9) t=1;
                    else if (j<=35) t=2;
                    else t=4;
                    (dp[id][j][k|t]+=sum[k]-dp[id^1][j][k]+P)%=P;
                }
            }
        }
//        for (int k=0;k<8;k++)
//        for (int j=0;j<=62;j++)
//            cout<<dp[id][j][k]<<" \n"[j==62];
//        cout<<"\n";
        for (int k=0;k<8;k++) sum[k]=0;
        for (int k=0;k<8;k++) {
            for (int j=0;j<62+(i==0);j++) {
                sum[k]=sum[k]+dp[id][j][k];
                dp[id^1][j][k]=0;
            }
            sum[k]%=P;
        }
    }
    ll ans=0;
    for (int j=0;j<62;j++) ans+=dp[id][j][7];
    cout<<ans%P<<'\n'; 
    return 0;
} 

