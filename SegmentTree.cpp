#include<bits/stdc++.h>
using namespace std;

// class to find minimum in a range
// point update
class SegTree {
    vector<int> seg;
    
    public:
    SegTree(n) {
        seg.resize(4 * n);
    }

    void build(int ind, int low, int high, vector<int> arr) {
        if(low == high) {
            seg[ind] = arr[low];
            return;
        }
        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = min(seg[2 * ind + 1], seg(2 * ind + 2));
    }

    int query(int ind, int low, int high, int l, int r) {
        if(r < low || high < l)
            return INT_MAX;
        if(low >= l && high <= r)
            return seg[ind];
        int mid = (low + high) / 2;
        int left = query(2 * ind + 1, low, mid, l, r);
        int right = query(2 * ind + 1, mid + 1, high, l, r);
        return min(left, right);
    }

    void update(int ind, int low, int high, int i, int val) {
        if(low == high) {
            seg[low] = val;
            return;
        }
        int mid = (left + right) / 2;
        if(i <= mid)
            update(2 * ind + 1, low, mid, i, val);
        else
            update(2 * ind + 2, mid + 1, high, i, val);
        seg[ind] = min(seg[2 * ind + 1], seg(2 * ind + 2));
    }
};





// class to find sum of a range
// range update
// lazy

class SegTree {
    vector<int> seg, lazy;
    public:
    SegTree(int n) {
        seg.resize(4 * n);
        lazy.resize(4 * n);  // initialize with 0
        for(int i = 0; i < lazy.size(); i ++)   lazy[i] = 0;
    }

    void build(int ind, int low, int high, vector<int> arr) {
        if(low == high) {
            seg[ind] = arr[low];
            return;
        }
        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    void update(int ind, int low, int high, int l, int r, int val) {
        // update the previous remaining updates
        // and propogate downwards
        if(lazy[ind] != 0) {
            seg[ind] += (high - low + 1) * lazy[ind];
            // propogate the lazy update downwards
            // for the rremaining node to get updated
            if(low != high) {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }
            lazy[ind] = 0;
        }

        // case 1
        // no overlap
        // we don't do anything and return
        if(r < low || high < l)
            return;

        // case 2
        // complete overlap
        if(low >= l && high <= r) {
            seg[ind] += (high - low + 1) * val;
            // then prppogate to childrens(if exists)
            if(low != high) {
                lazy[2 * ind + 1] += val;
                lazy[2 * ind + 2] += val;
            }
            return;
        }

        // case 3
        // partial overlap
        int mid = (low + high) / 2;
        update(2 * ind + 1, low, mid , l, r, val);
        update(2 * ind + 2, mid + 1, high, l, r, val);
        seg[ind] = seg[ind * 2 + 1] + seg[ind * 2 + 2];
    }

    int query(int ind, int low, int high, int l, int r) {
        // update the previous remaining updates
        // and propogate downwards
        if(lazy[ind] != 0) {
            seg[ind] += (high - low + 1) * lazy[ind];
            // propogate the lazy update downwards
            // for the rremaining node to get updated
            if(low != high) {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }
            lazy[ind] = 0;
        }

        // rest is same as value update
        if(r < low || high < l)
            return 0;
        if(low >= l && high <= r)
            return seg[ind];
        int mid = (low + high) / 2;
        int left = query(2 * ind + 1, low, mid, l, r);
        int right = query(2 * ind + 1, mid + 1, high, l, r);
        return left + right;
    }
};