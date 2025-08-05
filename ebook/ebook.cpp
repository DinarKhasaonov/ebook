#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>

using namespace std;

class ReadingManager {
public:
    void Read(int user_id, int page_count) {
        if (user_page.count(user_id)) {
            int prev_page = user_page[user_id];
            UpdateBIT(prev_page, -1);
        } else {
            ++active_users;
        }
        user_page[user_id] = page_count;
        UpdateBIT(page_count, 1);
    }

    double Cheer(int user_id) const {
        if (!user_page.count(user_id)) {
            return 0.0;
        }
        if (active_users == 1) {
            return 1.0;
        }
        int page = user_page.at(user_id);
        int count_behind = QueryBIT(page - 1);
        return static_cast<double>(count_behind) / (active_users - 1);
    }

private:
    static const int MAX_PAGE_COUNT = 1000;
    map<int, int> user_page;
    mutable vector<int> bit = vector<int>(MAX_PAGE_COUNT + 2, 0);
    int active_users = 0;

    // Добавляет delta к позиции index в BIT
    void UpdateBIT(int index, int delta) {
        for (; index <= MAX_PAGE_COUNT; index += index & -index) {
            bit[index] += delta;
        }
    }

    // Возвращает сумму в диапазоне [1..index]
    int QueryBIT(int index) const {
        int sum = 0;
        for (; index > 0; index -= index & -index) {
            sum += bit[index];
        }
        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;

    ReadingManager manager;
    for (int i = 0; i < Q; ++i) {
        string command;
        int user_id;
        cin >> command >> user_id;

        if (command == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (command == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << '\n';
        }
    }

    return 0;
}
