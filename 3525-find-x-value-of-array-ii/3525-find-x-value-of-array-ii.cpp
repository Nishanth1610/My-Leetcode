class Solution {
public:
    struct Node {
        long long cnt[5] = {};
        long long prod = 1;
        int len = 0;
    };

    int k;
    vector<Node> tree;
    vector<int> nums;

    Node merge(Node left, Node right) {
        if (left.len == 0) return right;
        if (right.len == 0) return left;

        Node res;
        res.len = left.len + right.len;

        // Product of the complete segment
        res.prod = (left.prod * right.prod) % k;

        // Prefixes completely inside the left segment
        for (int r = 0; r < k; r++) {
            res.cnt[r] += left.cnt[r];
        }

        // Prefixes that take all of left + a prefix of right
        for (int r = 0; r < k; r++) {
            int newR = (left.prod * r) % k;
            res.cnt[newR] += right.cnt[r];
        }

        return res;
    }

    Node makeNode(int value) {
        Node res;
        res.len = 1;
        res.prod = value % k;

        // The only non-empty prefix is the element itself
        res.cnt[res.prod] = 1;

        return res;
    }

    void build(int p, int l, int r) {
        if (l == r) {
            tree[p] = makeNode(nums[l]);
            return;
        }

        int mid = (l + r) / 2;

        build(p * 2, l, mid);
        build(p * 2 + 1, mid + 1, r);

        tree[p] = merge(tree[p * 2], tree[p * 2 + 1]);
    }

    void update(int p, int l, int r, int idx, int value) {
        if (l == r) {
            tree[p] = makeNode(value);
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(p * 2, l, mid, idx, value);
        else
            update(p * 2 + 1, mid + 1, r, idx, value);

        tree[p] = merge(tree[p * 2], tree[p * 2 + 1]);
    }

    Node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tree[p];

        int mid = (l + r) / 2;

        if (qr <= mid)
            return query(p * 2, l, mid, ql, qr);

        if (ql > mid)
            return query(p * 2 + 1, mid + 1, r, ql, qr);

        Node left = query(p * 2, l, mid, ql, qr);
        Node right = query(p * 2 + 1, mid + 1, r, ql, qr);

        return merge(left, right);
    }

    vector<int> resultArray(
        vector<int>& nums,
        int k,
        vector<vector<int>>& queries
    ) {
        this->nums = nums;
        this->k = k;

        int n = nums.size();

        tree.resize(4 * n);

        build(1, 0, n - 1);

        vector<int> answer;

        for (auto &q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            nums[index] = value;

            update(1, 0, n - 1, index, value);

            // We need all non-empty prefixes of nums[start...n-1]
            Node res = query(1, 0, n - 1, start, n - 1);

            answer.push_back(res.cnt[x]);
        }

        return answer;
    }
};