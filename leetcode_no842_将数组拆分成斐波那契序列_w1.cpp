/* ------------------------------------------------------------------|
给定一个数字字符串 S，比如 S = "123456579"，我们可以将它分成斐波那契式的序列 [123, 456, 579]。

形式上，斐波那契式序列是一个非负整数列表 F，且满足：

0 <= F[i] <= 2^31 - 1，（也就是说，每个整数都符合 32 位有符号整数类型）；
F.length >= 3；
对于所有的0 <= i < F.length - 2，都有 F[i] + F[i+1] = F[i+2] 成立。
另外，请注意，将字符串拆分成小块时，每个块的数字一定不要以零开头，除非这个块是数字 0 本身。

返回从 S 拆分出来的任意一组斐波那契式的序列块，如果不能拆分则返回 []。

 

示例 1：

输入："123456579"
输出：[123,456,579]
示例 2：

输入: "11235813"
输出: [1,1,2,3,5,8,13]
示例 3：

输入: "112358130"
输出: []
解释: 这项任务无法完成。
示例 4：

输入："0123"
输出：[]
解释：每个块的数字不能以零开头，因此 "01"，"2"，"3" 不是有效答案。
示例 5：

输入: "1101111"
输出: [110, 1, 111]
解释: 输出 [11,0,11,11] 也同样被接受。
 

提示：

1 <= S.length <= 200
字符串 S 中只含有数字。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/split-array-into-fibonacci-sequence
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。|
-------------------------------------------------------------------*/

/*	回溯法
*
*	执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
*	内存消耗：6.6 MB, 在所有 C++ 提交中击败了71.56%的用户
*/

#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}

};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool dfs(vector<int>& list,const string &S,const int& length,int index,long long sum,int prev) {
    //当进行到最后一位时，判断退出条件，要保证list里至少有三个数
    if (index == length) {
        return list.size() > 2;
    }
    //在index往后的字符串中寻找大小为sum的数
    long long cur = 0;
    for (int i = index; i < length; i++) {
        //子串不能以0开头，退出
        if (i > index && S[index] == '0') {
            break;
        }
        //循环计算cur
        cur = cur * 10 + S[i] - '0';
        //子串不能大于INTMAX，退出
        if (cur > INT_MAX) {
            break;
        }
        //当list里的元素大于2时，可以开始判断cur和sum的大小关系
        if (list.size() >= 2) {
            //小于sum继续循环
            if (cur < sum) {
                continue;
            }
            //大于sum就退出
            else if (cur > sum) {
                break;
            }
        }
        //恰好等于sum时，压入list
        list.push_back(cur);
        //从i+1开始往下继续递归，将sum更新为prev+sum，将prev更新为sum
        if (dfs(list, S, length, i + 1, prev + cur, cur)) {
            return true;
        }
        //如果有错误，弹出之前压入的数
        list.pop_back();
    }
    return false;
}

vector<int> splitIntoFibonacci(string S) {
    vector<int> list;
    int length = S.length();
    dfs(list, S, length, 0, 0, 0);
    return list;
}
