#include <iostream>
#include <iomanip>
#include <map>
#include <string>

using namespace std;

class ReadingManager {
public:
    void Read(int user_id, int page_count) {
        if (user_page.count(user_id)) {
            int prev_page = user_page[user_id];
            --page_stat[prev_page];
            if (page_stat[prev_page] == 0) {
                page_stat.erase(prev_page); // Чистим статистику
            }
        } else {
            ++active_users;
        }
        user_page[user_id] = page_count;
        ++page_stat[page_count];
    }

    double Cheer(int user_id) const {
        if (!user_page.count(user_id)) {
            return 0.0;
        }
        if (active_users == 1) {
            return 1.0;
        }

        int user_page_num = user_page.at(user_id);
        int count_behind = 0;

        for (auto it = page_stat.begin(); it != page_stat.end() && it->first < user_page_num; ++it) {
            count_behind += it->second;
        }

        return static_cast<double>(count_behind) / (active_users - 1);
    }

private:
    map<int, int> user_page;  // user_id -> current page
    map<int, int> page_stat;  // page number -> user count
    int active_users = 0;
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
