#include <stdio.h>

struct UserAccount {
    int account_id;
    int plan_type;
    int monthly_fee;
    int remaining_days;
    int active_devices;
};

int main() {
    int n, i, j;
    struct UserAccount accounts[100];
    struct UserAccount active_accounts[100];
    struct UserAccount free_accounts[100];
    int active_count = 0;
    int free_count = 0;
    long long old_mrr = 0;
    long long new_mrr = 0;

    do {
        printf("Nhap so luong tai khoan N (1 <= N <= 100): ");
        scanf("%d", &n);
    } while (n < 1 || n > 100);

    for (i = 0; i < n; i++) {
        printf("\nTai khoan thu %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &accounts[i].account_id);
        
        do {
            printf("Plan Type (0-Free, 1-Standard, 2-Premium): ");
            scanf("%d", &accounts[i].plan_type);
        } while (accounts[i].plan_type < 0 || accounts[i].plan_type > 2);
        
        printf("Monthly Fee (hien tai): ");
        scanf("%d", &accounts[i].monthly_fee);
        
        printf("Remaining Days: ");
        scanf("%d", &accounts[i].remaining_days);
        
        printf("Active Devices: ");
        scanf("%d", &accounts[i].active_devices);
        
        old_mrr += accounts[i].monthly_fee;
    }

    for (i = 0; i < n; i++) {
        if (accounts[i].active_devices <= 0) {
            accounts[i].active_devices = 1;
        }

        if (accounts[i].remaining_days <= 0) {
            accounts[i].plan_type = 0;
            if (accounts[i].remaining_days < 0) {
                accounts[i].remaining_days = 0;
            }
        }

        if (accounts[i].plan_type == 0) {
            accounts[i].monthly_fee = 0;
            if (accounts[i].active_devices > 1) {
                accounts[i].active_devices = 1;
            }
        } else if (accounts[i].plan_type == 1) {
            accounts[i].monthly_fee = 120000;
            if (accounts[i].active_devices > 2) {
                accounts[i].active_devices = 2;
            }
        } else if (accounts[i].plan_type == 2) {
            accounts[i].monthly_fee = 300000;
            if (accounts[i].active_devices > 5) {
                accounts[i].active_devices = 5;
            }
        }

        if (accounts[i].plan_type > 0) {
            active_accounts[active_count] = accounts[i];
            active_count++;
            new_mrr += accounts[i].monthly_fee;
        } else {
            free_accounts[free_count] = accounts[i];
            free_count++;
        }
    }

    for (i = 0; i < active_count - 1; i++) {
        for (j = 0; j < active_count - i - 1; j++) {
            if (active_accounts[j].monthly_fee < active_accounts[j + 1].monthly_fee) {
                struct UserAccount temp = active_accounts[j];
                active_accounts[j] = active_accounts[j + 1];
                active_accounts[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < active_count; i++) {
        accounts[i] = active_accounts[i];
    }
    for (i = 0; i < free_count; i++) {
        accounts[active_count + i] = free_accounts[i];
    }

    printf("\n=== DANH SACH TAI KHOAN SAU KIEM TOAN ===\n");
    printf("%-10s %-10s %-15s %-15s %-15s\n", "ID", "PLAN", "FEE (VND)", "REMAIN_DAYS", "DEVICES");
    printf("----------------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%-10d %-10d %-15d %-15d %-15d\n",
               accounts[i].account_id,
               accounts[i].plan_type,
               accounts[i].monthly_fee,
               accounts[i].remaining_days,
               accounts[i].active_devices);
    }
    printf("----------------------------------------------------------------------\n");
    printf("MRR Du Kien Ban Dau: %lld VND\n", old_mrr);
    printf("MRR Thuc Te Hien Tai: %lld VND\n", new_mrr);

    return 0;
}
