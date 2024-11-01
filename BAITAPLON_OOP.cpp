#include <iostream>     // Nhập/xuất dữ liệu
#include <fstream>      // Đọc/ghi dữ liệu vào file
#include <iomanip>      // Định dạng đầu ra
#include <string>       // Xử lý chuỗi
#include <vector>       // Lưu trữ danh sách tài khoản, giao dịch
#include <map>          // (Tùy chọn) Sử dụng nếu cần ánh xạ các cặp key-value
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <ctime>

using namespace std;
fstream account_file("@account_database.txt", ios::in | ios::out); // Mở file database dạng đọc và ghi
fstream transaction_file("@transaction_database.txt", ios::in | ios::out); // Mở file database dạng đọc và ghi
fstream category_file("@category_database.txt", ios::in | ios::out); // Mở file database dạng đọc và ghi

class GiaoDich {
private:
    string idGiaoDich;          // ID cua giao dich
    string ngayGiaoDich;        // Ngay giao dich
    string loaiGiaoDich;        // Loai giao dich (VD: "Nap tien", "Rut tien")
    double soTien;              // So tien cua giao dich
    string danhMuc;             // Danh muc giao dich (VD: "An uong", "Giai tri")
    string ghiChu;              // Ghi chu ve giao dich
    string soTaiKhoan;          // So tai khoan cua giao dich

public:
    // Constructor khoi tao giao dich
    GiaoDich(string stk, string id, string ngay, string loai, double tien, string dm, string note = "")
        : soTaiKhoan(stk), idGiaoDich(id), ngayGiaoDich(ngay), loaiGiaoDich(loai), soTien(tien), danhMuc(dm), ghiChu(note) {}
    string getID() const {
        return idGiaoDich;
    }
    void setID(string id)
    {
        
    }
    string getNgayGiaoDich() const {
        return ngayGiaoDich;
    }
    string getLoaiGiaoDich() const {
        return loaiGiaoDich;
    }
    double getSoTien() const {
        return soTien;
    }
    string getDanhMuc() const {
        return danhMuc;
    }
    string getGhiChu() const {
        return ghiChu;
    }
    string getSoTaiKhoan() const {
        return soTaiKhoan;
    }
    // Phuong thuc in thong tin giao dich
    void inGiaoDich() const {
        cout << left << setw(15) << "ID giao dich: " << idGiaoDich << endl;
        cout << left << setw(15) << "Ngay giao dich: " << ngayGiaoDich << endl;
        cout << left << setw(15) << "Loai giao dich: " << loaiGiaoDich << endl;
        cout << left << setw(15) << "So tien: " <<fixed<< setprecision(0)<< soTien << " VND"<<endl;
        cout << left << setw(15) << "Danh muc: " << danhMuc << endl;
        cout << left << setw(15) << "Ghi chu: " << (ghiChu.empty() ? "Khong co" : ghiChu) << endl;
    }

    // Phuong thuc them giao dich vao database
    void addTransactionToDB() const {
        fstream transaction_file("@transaction_database.txt", ios::app); // Mo file de ghi
        if (transaction_file.is_open()) {
            transaction_file << endl;
            transaction_file << left << setw(15) << "So tai khoan: " << soTaiKhoan << endl;
            transaction_file << left << setw(15) << "ID giao dich: " << idGiaoDich << endl;
            transaction_file << left << setw(15) << "Ngay giao dich: " << ngayGiaoDich << endl;
            transaction_file << left << setw(15) << "Loai giao dich: " << loaiGiaoDich << endl;
            transaction_file << left << setw(15) << "So tien: "<<fixed<< setprecision(0) << soTien << endl;
            transaction_file << left << setw(15) << "Danh muc: " << danhMuc << endl;
            transaction_file << left << setw(15) << "Ghi chu: " << (ghiChu.empty() ? "Khong co" : ghiChu) << endl;
            transaction_file.close();
            cout << "Giao dich da duoc luu vao database." << endl;
        }
        else {
            cerr << "Khong the mo file @transaction_database.txt de ghi du lieu." << endl;
        }
    }

    // Phuong thuc tim giao dich theo ID
    bool timGiaoDich(const string& id) const {
        return id == idGiaoDich;
    }

    // Phuong thuc sua thong tin giao dich
    void chinhSuaGiaoDich() {
        cout << "Chinh sua giao dich ID: " << idGiaoDich << endl;
        cout << "Nhap lai ngay giao dich (dd/mm/yyyy): "; cin >> ngayGiaoDich;
        cout << "Nhap lai loai giao dich (Nap tien/Rut tien): "; cin >> loaiGiaoDich;
        cout << "Nhap lai so tien giao dich: "; cin >> soTien;
        cout << "Nhap lai danh muc giao dich: "; cin.ignore(); getline(cin, danhMuc);
        cout << "Nhap lai ghi chu (neu co): "; getline(cin, ghiChu);
    }
};
class DanhMucChiTieu {
private:
    string tenDanhMuc;
    double gioiHanChi;
    string soTaiKhoan;
    double soTienDaChi;
public:
    // Constructor
    DanhMucChiTieu(string stk, string ten, double gioiHan = 0, double soTienDaChi = 0)
        : soTaiKhoan(stk), tenDanhMuc(ten), gioiHanChi(gioiHan), soTienDaChi(soTienDaChi) {}

    string getTenDanhMuc() const {
        return tenDanhMuc;
    }

    // Phương thức thiết lập giới hạn chi tiêu
    void thietLapGioiHan(double gioiHan) {
        gioiHanChi = gioiHan;
        cout << "Da thiet lap gioi han chi tieu cho danh muc " << tenDanhMuc << ": " << gioiHanChi << " VND" << endl;
    }

    // Phương thức thêm chi phí vào danh mục
    void themChiPhi(double soTien) {
        soTienDaChi += soTien;
        cout << "Da them " << soTien << " VND vao danh muc " << tenDanhMuc << ". Tong chi tieu hien tai: " << soTienDaChi << " VND" << endl;
    }

    // Phương thức kiểm tra xem đã vượt giới hạn chi tiêu chưa
    bool kiemTraGioiHan() const {
        if (soTienDaChi > gioiHanChi) {
            cout << "Canh bao: Chi tieu da vuot gioi han cho danh muc " << tenDanhMuc << "!" << endl;
            return true;
        }
        return false;
    }

    // Phương thức in thông tin danh mục
    void inDanhMuc() const {
        cout << left << setw(20) << "Danh muc: " << tenDanhMuc << endl;
        cout << left << setw(20) << "Gioi han chi tieu: " <<fixed<< setprecision(0)<< gioiHanChi << " VND" << endl;
        cout << left << setw(20) << "Tong chi tieu: " <<fixed<< setprecision(0)<< soTienDaChi << " VND" << endl;
    }

    // Phương thức lưu thông tin danh mục vào file
    void luuDanhMucVaoDB() {
        fstream category_file("@category_database.txt", ios::app);
        if (category_file.is_open()) {
            category_file << endl;
            category_file << left << setw(20) << "So tai khoan: " << soTaiKhoan << endl;
            category_file << left << setw(20) << "Danh muc: " << tenDanhMuc << endl;
            category_file << left << setw(20) << "Gioi han chi tieu: " << fixed<< setprecision(0) << " VND" << endl;
            category_file << left << setw(20) << "Tong chi tieu: " <<fixed<< setprecision(0)<< soTienDaChi << " VND" << endl;
            category_file.close();
        }
        else {
            cerr << "Khong the mo file @category_database.txt de ghi du lieu." << endl;
        }
    }
    // Phương thức đọc thông tin danh mục từ file
    void docDanhMucTuDB()
    {
        fstream category_db_read("@category_database.txt", ios::in);
        string line;

        if (category_db_read.is_open())
        {
            while (getline(category_db_read, line))
            {
                if (line.find("Danh muc: ") != string::npos)
                {
                    tenDanhMuc = line.substr(10);
                }
                else if (line.find("Gioi han chi tieu: ") != string::npos)
                {
                    gioiHanChi = stod(line.substr(20));
                }
                else if (line.find("Tong chi tieu: ") != string::npos)
                {
                    soTienDaChi = stod(line.substr(15));
                }
            }
        }
        category_db_read.close();
    }

};
class taikhoan {
private:
    string soTaiKhoan;         // Số tài khoản hoặc tên tài khoản
    string loaiTaiKhoan;       // Loại tài khoản (tiền mặt, thẻ ngân hàng, ví điện tử, v.v.)
    double soDu;               // Số dư hiện tại của tài khoản
    string nganHangLienKet;    // Tên ngân hàng liên kết (nếu có)
    vector<GiaoDich> danhSachGiaoDich; // Danh sách các giao dịch thuộc về tài khoản
    vector<DanhMucChiTieu> danhSachDanhMuc; // Danh sách các danh mục chi tiêu thuộc tài khoản

public:
    // Constructor
    taikhoan() {}
    taikhoan(string soTk, string loaiTk, double soTien, string nganHang = "")
        : soTaiKhoan(soTk), loaiTaiKhoan(loaiTk), soDu(soTien), nganHangLienKet(nganHang) {}
    string getSoTaiKhoan() const {
        return soTaiKhoan;
    }
    const vector<DanhMucChiTieu>& getDanhSachDanhMuc() const {
        return danhSachDanhMuc;
    }
    // Phương thức nhập thông tin tài khoản từ người dùng
    void khoiTaoTaiKhoan() {
        cout << "Nhap so tai khoan: "; cin >> soTaiKhoan;
        cout << "Nhap loai tai khoan: "; cin.ignore(); getline(cin, loaiTaiKhoan);
        cout << "Nhap so du ban dau: "; cin >> soDu;
        cout << "Nhap ngan hang lien ket (neu co): "; cin.ignore(); getline(cin, nganHangLienKet);
    }
    
    //Ham khoi phuc du lieu giao dich
    void storageDatabaseCurrent()
    {
        fstream transaction_db_read("@transaction_database.txt", ios::in);
        string line;
        if (transaction_db_read.is_open())
        {
            while (getline(transaction_db_read, line))
            {
                if (line.find("So tai khoan: ") != string::npos)
                {
                    string id, ngay, loai, danhMuc, ghiChu;
                    double soTien;

                    // Đọc từng dòng giao dịch
                    getline(transaction_db_read, line);
                    id = line.substr(15);
                    getline(transaction_db_read, line);
                    ngay = line.substr(15);
                    getline(transaction_db_read, line);
                    loai = line.substr(15);
                    getline(transaction_db_read, line);
                    soTien = stod(line.substr(15));
                    getline(transaction_db_read, line);
                    danhMuc = line.substr(15);
                    getline(transaction_db_read, line);
                    ghiChu = line.substr(15);
                    GiaoDich gd(soTaiKhoan, id, ngay, loai, soTien, danhMuc, ghiChu);
                    danhSachGiaoDich.push_back(gd);
                }
            }
            transaction_db_read.close();
        }
    }
    
    //Ham khoi phuc du lieu danh muc
  void restoreCategoryDatabase()
{
    fstream category_db_read("@category_database.txt", ios::in);
    string line;
    if (category_db_read.is_open()) {
        while (getline(category_db_read, line)) {
            if (line.find("Số tài khoản: " + soTaiKhoan) != string::npos) {
                string tenDanhMuc;
                double gioiHanChi, soTienDaChi;

                // Đọc từng dòng danh mục chi tiêu
                getline(category_db_read, line); tenDanhMuc = line.substr(10);
                getline(category_db_read, line); gioiHanChi = stod(line.substr(20));
                getline(category_db_read, line); soTienDaChi = stod(line.substr(15));

                // Tạo đối tượng DanhMucChiTieu và thêm vào danh sách danh mục
                DanhMucChiTieu dm(soTaiKhoan, tenDanhMuc, gioiHanChi, soTienDaChi);
                danhSachDanhMuc.push_back(dm);
            }
        }
        category_db_read.close();
    }
}
   string layThoiGianHienTai() {
    // Lấy thời gian hiện tại
    auto now = chrono::system_clock::now(); 
    auto ngayGio = chrono::system_clock::to_time_t(now); 
    tm *ptm = localtime(&ngayGio); // Chuyển đổi thành cấu trúc thời gian

    // Chuyển đổi thành chuỗi định dạng "YYYY-MM-DD HH:MM:SS"
    stringstream ss;
    ss << put_time(ptm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

   void napTien(double soTien) {
    if (soTien > 0) {
        soDu += soTien;
        string id = "GD" + to_string(danhSachGiaoDich.size() + 1);
        string thoiGianGiaoDich = layThoiGianHienTai(); // Lấy thời gian hiện tại
        
        GiaoDich giaoDich(soTaiKhoan, id, thoiGianGiaoDich, "Nap tien", soTien, "Thu nhap");
        
        danhSachGiaoDich.push_back(giaoDich); // Thêm giao dịch vào danh sách
        giaoDich.addTransactionToDB(); // Ghi giao dịch vào DB
        
        // In thông tin giao dịch với thời gian rõ ràng
        cout << fixed << setprecision(0);
        cout << "Da nap " << soTien << " vao tai khoan. So du hien tai: " << soDu << endl;
        cout << "Thoi gian giao dich: " << thoiGianGiaoDich << endl; // In thời gian giao dịch
    } else {
        cout << "So tien nap khong hop le." << endl;
    }
}

    void rutTien(double soTien) {
        if (soTien > 0 && soTien <= soDu) {
            soDu -= soTien;
            string id = "GD" + to_string(danhSachGiaoDich.size() + 1);
            string thoiGianGiaoDich=layThoiGianHienTai();
            GiaoDich giaoDich(soTaiKhoan, id, thoiGianGiaoDich, "Rut tien", soTien, "Chi tieu"); // Giao dich kem so tai khoan
            danhSachGiaoDich.push_back(giaoDich);
            giaoDich.addTransactionToDB(); // Ghi giao dich vao DB
            cout << fixed << setprecision(0);
            cout << "Da rut " << soTien << " tu tai khoan. So du hien tai: " << soDu << endl;
        }
        else {
            cout << "So du khong du hoac so tien khong hop le." << endl;
        }
    }

    void truTien(double soTien) {
        if (soDu >= soTien) {
            soDu -= soTien;
            cout << "So du sau khi tru: "<<fixed<< setprecision(0) << soDu << " VND" << endl;
        }
        else {
            cout << "So du khong du de thuc hien giao dich nay." << endl;
            return; // Khong thuc hien tru so du neu khong du tien
        }

        // Kiem tra sau khi tru tien neu so du nho hon 0
        if (soDu < 0) {
            cout << "Canh bao: Ban dang no "<<fixed<< setprecision(0) << -soDu << " VND." << endl;
        }
    }

    // Phương thức thêm giao dịch
    void themGiaoDich(const GiaoDich& giaoDich) {
        // Kiểm tra tính hợp lệ của giao dịch trước khi thêm
        if (giaoDich.getID().empty() || giaoDich.getNgayGiaoDich().empty() ||
            giaoDich.getLoaiGiaoDich().empty() || giaoDich.getDanhMuc().empty() ||
            giaoDich.getSoTien() <= 0) {
            cout << "Loi: Thieu thong tin hoac so tien khong hop le. Khong the them giao dich." << endl;
            return;
        }

        danhSachGiaoDich.push_back(giaoDich);
        giaoDich.addTransactionToDB(); // Ghi giao dịch vào database
        cout << "Giao dich da duoc them thanh cong vao danh sach va luu vao database." << endl;
    }

    double xemSoDu() const {
        cout << "So du hien tai cua tai khoan: " << fixed<< setprecision(0)<< soDu<<" VND" << endl;
        return soDu;
    }

    void addAccountToDB() {
        account_file << endl;
        account_file << left << setw(15) << "So tai khoan: " << soTaiKhoan << endl;
        account_file << left << setw(15) << "Loai tai khoan: " << loaiTaiKhoan << endl;
        account_file << left << setw(12) << "So du: "<< fixed<< setprecision(0) << soDu<<" VND" << endl;
        account_file << left << setw(20) << "Ngan hang lien ket: " << (nganHangLienKet.empty() ? "Khong co" : nganHangLienKet) << endl;
    }

    void docAccountFromDB() {
        fstream account_db_read("@account_database.txt", ios::in);
        string line;

        if (account_db_read.is_open()) {
            while (getline(account_db_read, line)) {
                if (line.find("So tai khoan: ") != string::npos) {
                    soTaiKhoan = line.substr(15);
                }
                else if (line.find("Loai tai khoan: ") != string::npos) {
                    loaiTaiKhoan = line.substr(15);
                }
                else if (line.find("So du: ") != string::npos) {
                    soDu = stod(line.substr(12));
                }
                else if (line.find("Ngan hang lien ket: ") != string::npos) {
                    nganHangLienKet = line.substr(20);
                }
            }
        }
        account_db_read.close();
    }

    void inTaiKhoan() const {
        cout << left << setw(15) << "So tai khoan: " << soTaiKhoan << endl;
        cout << left << setw(15) << "Loai tai khoan: " << loaiTaiKhoan << endl;
        cout << left << setw(12) << "So du: " << fixed<< setprecision(0)<< soDu <<" VND"<< endl;
        cout << left << setw(20) << "Ngan hang lien ket: " << (nganHangLienKet.empty() ? "Khong co" : nganHangLienKet) << endl;
    }

    void capNhatSoDuVaoDB() {
        fstream tempFile("@temp_account_database.txt", ios::out);
        fstream account_db_read("@account_database.txt", ios::in);

        string line;
        bool daCapNhat = false;

        while (getline(account_db_read, line)) {
            if (line.find("So tai khoan: ") != string::npos && line.substr(15) == soTaiKhoan) {
                tempFile << line << endl;
                getline(account_db_read, line);
                tempFile << line << endl;
                getline(account_db_read, line);
                tempFile << left << setw(12) << "So du: " << fixed<< setprecision(0)<< soDu << endl;
                daCapNhat = true;
                getline(account_db_read, line);
                tempFile << line << endl;
            }
            else {
                tempFile << line << endl;
            }
        }

        if (!daCapNhat) {
            tempFile << endl;
            tempFile << left << setw(15) << "So tai khoan: " << soTaiKhoan << endl;
            tempFile << left << setw(15) << "Loai tai khoan: " << loaiTaiKhoan << endl;
            tempFile << left << setw(12) << "So du: " << fixed<< setprecision(0)<< soDu << endl;
            tempFile << left << setw(20) << "Ngan hang lien ket: " << (nganHangLienKet.empty() ? "Khong co" : nganHangLienKet) << endl;
        }

        account_db_read.close();
        tempFile.close();

        remove("@account_database.txt");
        rename("@temp_account_database.txt", "@account_database.txt");
    }

    void themGiaoDichVaoDanhMuc(const string& tenDanhMuc, double soTien) {
        bool danhMucTonTai = false;
        for (auto& dm : danhSachDanhMuc) {
            if (dm.getTenDanhMuc() == tenDanhMuc) {
                dm.themChiPhi(soTien);
                dm.kiemTraGioiHan();
                danhMucTonTai = true;
                break;
            }
        }
        if (!danhMucTonTai) {
            cout << "Danh muc " << tenDanhMuc << " khong ton tai. Vui long tao danh muc nay truoc." << endl;
        }
    }

    void themDanhMuc(const DanhMucChiTieu& danhMuc) {
        danhSachDanhMuc.push_back(danhMuc);
        cout << "Da them mot danh muc chi tieu moi vao tai khoan." << endl;
    }

    void inTatCaGiaoDich() const {
        if (danhSachGiaoDich.empty()) {
            cout << "Khong co giao dich nao." << endl;
        }
        else {
            cout << "Danh sach cac giao dich:" << endl;
            for (const auto& giaoDich : danhSachGiaoDich) {
                giaoDich.inGiaoDich();
                cout << "------------------------" << endl;
            }
        }
    }

    void inTatCaDanhMuc() const {
        if (danhSachDanhMuc.empty()) {
            cout << "Khong co danh muc chi tieu nao." << endl;
        }
        else {
            for (const auto& danhMuc : danhSachDanhMuc) {
                danhMuc.inDanhMuc();
                cout << "------------------------" << endl;
            }
        }
    }
};

vector<taikhoan> danhSachTaiKhoan;   // Danh sách các tài khoản
taikhoan *taiKhoanHienTai = nullptr; // Con trỏ đến tài khoản hiện tại

taikhoan *timTaiKhoan(const string &soTaiKhoan)
{
    fstream account_db("@account_database.txt", ios::in);
    if (!account_db.is_open())
    {
        cerr << "Khong the mo file database." << endl;
        return nullptr;
    }

    string line, stk, loaiTk, nganHang;
    double soDu;
    bool timThayTaiKhoan = false;

    // Đọc từng dòng trong file cho đến khi tìm thấy số tài khoản
    while (getline(account_db, line))
    {
        if (line.find("So tai khoan: ") != string::npos)
        {
            stk = line.substr(15); // Lấy số tài khoản sau "So tai khoan: "
            if (stk == soTaiKhoan)
            {
                timThayTaiKhoan = true;
            }
        }
        else if (timThayTaiKhoan && line.find("Loai tai khoan: ") != string::npos)
        {
            loaiTk = line.substr(15);
        }
        else if (timThayTaiKhoan && line.find("So du: ") != string::npos)
        {
            soDu = stod(line.substr(12));
        }
        else if (timThayTaiKhoan && line.find("Ngan hang lien ket: ") != string::npos)
        {
            nganHang = line.substr(20);
            // Tạo tài khoản và trả về
            taikhoan *tkMoi = new taikhoan(stk, loaiTk, soDu, nganHang);
            account_db.close();
            return tkMoi;
        }
    }

    account_db.close();
    return nullptr;
}

//sinh id cho moi giao dich
string taoIdUser() 
{  string maGiaoDich;

    // Tạo 2 chữ cái in hoa
    for (int i = 0; i < 2; ++i) {
        char letter = 'A' + rand() % 26; // Chọn ngẫu nhiên từ A-Z
        maGiaoDich += letter;
    }

    // Tạo 7 chữ số
    for (int i = 0; i < 7; ++i) {
        int number = rand() % 10; // Chọn ngẫu nhiên từ 0-9
        maGiaoDich += to_string(number);
    }

    return maGiaoDich;
}


// Hàm đăng nhập hoặc tạo tài khoản mới nếu không tồn tại
void logIn()
{
    string find_soTaiKhoan;
    cout <<setw(20)<< "Dang nhap:" << endl;
    cout << "Nhap so tai khoan cua ban: ";
    getline(cin, find_soTaiKhoan);

    // Tìm tài khoản theo số tài khoản
    taiKhoanHienTai = timTaiKhoan(find_soTaiKhoan);

    if (taiKhoanHienTai)
    {
        cout << "Xin chao! Dang nhap thanh cong voi so tai khoan: " << find_soTaiKhoan << endl;
        fstream transaction_db_read("@transaction_database.txt", ios::in);
        fstream category_db_read("@category_database.txt", ios::in);
        taiKhoanHienTai->storageDatabaseCurrent();
//        taiKhoanHienTai->restoreCategoryDatabase();
    }
    else
    {
        cout << "Tai khoan khong ton tai. Ban co muon tao tai khoan moi khong? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            string loaiTaiKhoan, nganHang;
            double soTien;
            cout << "Nhap loai tai khoan (tien mat, vi dien tu, v.v.): ";
            cin.ignore();
            getline(cin, loaiTaiKhoan);
            cout << "Nhap so du ban dau: ";
            cin >> soTien;
            cout << "Nhap ten ngan hang lien ket (neu co): ";
            cin.ignore();
            getline(cin, nganHang);

            // Tạo tài khoản mới và thêm vào danh sách tài khoản
            taikhoan tkMoi(find_soTaiKhoan, loaiTaiKhoan, soTien, nganHang);
            tkMoi.addAccountToDB(); // Lưu tài khoản mới vào file database
            danhSachTaiKhoan.push_back(tkMoi);
            taiKhoanHienTai = &danhSachTaiKhoan.back(); // Cập nhật tài khoản hiện tại
            cout << "Tai khoan moi da duoc tao thanh cong va dang nhap.\n";
        }
        else
        {
            cout << "Dang nhap that bai!\n";
            cout<<"Ban can dang nhap truoc khi chon chuc nang!"<< endl;
            cout<< endl;
            logIn();
        }
    }
}
void docTatCaTaiKhoan()
{
    fstream account_db_read("@account_database.txt", ios::in);
    string line;

    if (account_db_read.is_open())
    {
        while (getline(account_db_read, line))
        {
            string soTaiKhoan, loaiTaiKhoan, nganHangLienKet;
            double soDu = 0.0;

            if (line.find("So tai khoan: ") != string::npos || line.find("Số tài khoản: ") != string::npos)
            {
                soTaiKhoan = line.substr(line.find(": ") + 2);

                // Đọc các dòng tiếp theo để lấy các thuộc tính còn lại
                getline(account_db_read, line);
                loaiTaiKhoan = line.substr(line.find(": ") + 2);
                getline(account_db_read, line);
                soDu = stod(line.substr(line.find(": ") + 2));
                getline(account_db_read, line);
                nganHangLienKet = line.substr(line.find(": ") + 2);

                // Tạo tài khoản mới và thêm vào danh sách tài khoản
                taikhoan tkMoi(soTaiKhoan, loaiTaiKhoan, soDu, nganHangLienKet);
                danhSachTaiKhoan.push_back(tkMoi);
            }
        }
        account_db_read.close();
    }
    else
    {
        cerr << "Khong the mo file @account_database.txt de doc tai khoan." << endl;
    }
}
// Hàm chọn chức năng
void chonMode(int &mode)
{
    if (!taiKhoanHienTai)
    {
        cout << "Ban can dang nhap truoc khi chon chuc nang.\n";
        return;
    }
    do
    {
        cout << endl
             << "--------------------------------------------\n"
             << "Chon chuc nang duoi day:" << endl
             << endl
             << "1. Nap tien vao tai khoan" << endl
             << "2. Rut tien tu tai khoan" << endl
             << "3. Them giao dich" << endl
             << "4. Xem cac giao dich" << endl
             << "5. Them danh muc chi tieu" << endl
             << "6. Xem cac danh muc chi tieu" << endl
             << "7. Kiem tra no" << endl
             << "\n0. Ket thuc" << endl
             << endl;
        cout << "Nhap chuc nang (0-7) ban muon thuc hien: ";
        cin >> mode;
    } while (mode > 7 || mode < 0);

    // Xử lý các chế độ cho từng chức năng
    switch (mode)
    {
    case 1:
    { // Nạp tiền vào tài khoản
        double soTien;
        cout << "Nhap so tien muon nap: ";
        cin >> soTien;
        taiKhoanHienTai->napTien(soTien);    // Nạp tiền vào tài khoản hiện tại
        taiKhoanHienTai->capNhatSoDuVaoDB(); // Cập nhật số dư vào file
        break;
    }
    case 2:
    { // Rút tiền từ tài khoản
        double soTien;
        cout << "Nhap so tien muon rut: ";
        cin >> soTien;
        taiKhoanHienTai->rutTien(soTien);    // Rút tiền từ tài khoản hiện tại
        taiKhoanHienTai->capNhatSoDuVaoDB(); // Cập nhật số dư vào file
        break;
    }
        // Thêm giao dịch mới
    // Thêm giao dịch mới
    case 3:
    {
        string ngay, loai, danhMuc, ghiChu;
        double soTien;

        cout << "Nhap ngay giao dich (dd/mm/yyyy): ";
        cin >> ngay;
        cout << "Nhap loai giao dich (thu nhap/chi tieu): ";
        cin.ignore();
        getline(cin, loai);
        // Đảm bảo rằng soTien là số hợp lệ và không âm
        cout << "Nhap so tien giao dich: ";
        while (true)
        {
            cin >> soTien;
            if (cin.fail() || soTien <= 0)
            { // Kiểm tra nếu nhập không phải là số hoặc là số âm/0
                cout << "So tien khong hop le. Vui long nhap lai: ";
                cin.clear();                                         // Xóa trạng thái lỗi
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bỏ qua các ký tự còn lại trong dòng
            }
            else
            {
                break; // Thoát khỏi vòng lặp nếu nhập hợp lệ
            }
        }

        cout << "Nhap danh muc giao dich: ";
        cin.ignore(); // Bỏ ký tự xuống dòng còn lại trước khi lấy dòng tiếp theo
        getline(cin, danhMuc);
        cout << "Nhap ghi chu (neu co): ";
        getline(cin, ghiChu);

        // Kiểm tra danh mục có tồn tại hay không
        bool danhMucTonTai = false;
        for (const auto &dm : taiKhoanHienTai->getDanhSachDanhMuc())
        {
            if (dm.getTenDanhMuc() == danhMuc)
            {
                danhMucTonTai = true;
                break;
            }
        }
        if (!danhMucTonTai)
        {
            cout << "Danh muc " << danhMuc << " khong ton tai. Vui long tao danh muc truoc khi them giao dich." << endl;
            break;
        }

        // Thêm giao dịch
        GiaoDich gd(taiKhoanHienTai->getSoTaiKhoan(), taoIdUser(), ngay, loai, soTien, danhMuc, ghiChu);
        taiKhoanHienTai->themGiaoDich(gd);
        taiKhoanHienTai->truTien(soTien);
        taiKhoanHienTai->themGiaoDichVaoDanhMuc(danhMuc, soTien);
        break;
    }

    case 4:
    { // Xem tất cả các giao dịch
        cout << "\nDanh sach giao dich: " << endl;
        taiKhoanHienTai->inTatCaGiaoDich(); // In tất cả giao dịch của tài khoản hiện tại
        break;
    }
    case 5:
    { // Thêm danh mục chi tiêu
        string tenDanhMuc;
        double gioiHan;
        cout << "Nhap ten danh muc chi tieu: ";
        cin.ignore();
        getline(cin, tenDanhMuc);
        cout << "Nhap gioi han chi tieu cho danh muc nay: ";
        cin >> gioiHan;

        string soTaiKhoan = taiKhoanHienTai->getSoTaiKhoan();    // Giả sử phương thức này có sẵn
        DanhMucChiTieu danhMuc(soTaiKhoan, tenDanhMuc, gioiHan); // Tạo danh mục mới với đầy đủ tham số
        taiKhoanHienTai->themDanhMuc(danhMuc);                   // Thêm danh mục vào tài khoản hiện tại
        danhMuc.luuDanhMucVaoDB();                               // Lưu danh mục vào file
        break;
    }
    case 6:
    { // Xem các danh mục chi tiêu
        cout << "\nDanh sach cac danh muc chi tieu: " << endl;
        taiKhoanHienTai->inTatCaDanhMuc(); // In tất cả danh mục của tài khoản hiện tại
        break;
    }
    case 7:
    { // Kiểm tra nợ
        if (taiKhoanHienTai->xemSoDu() < 0)
        {
            cout << "Ban dang no " << -taiKhoanHienTai->xemSoDu() << " VND." << endl;
        }
        else
        {
            cout << "Ban khong co no." << endl;
        }
        break;
    }
    case 0:
        cout << "Ket thuc chuong trinh." << endl;
        break;
    }
}
// Hàm main
int main()
{
    cout<< "Quan ly chi tieu HAIDANG - CHI TIEU THEO CACH CUA BAN!"<< endl;
    srand(time(0));
//    docTatCaTaiKhoan();
    int mode = 1;
    // Đăng nhập hoặc tạo tài khoản mới
    logIn();

    // Vòng lặp chương trình
    while (mode)
    {
        chonMode(mode);
    }

    return 0;
}