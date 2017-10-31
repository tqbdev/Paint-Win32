# Readme for deadline Paint
### ---------------- INFO ----------------
1. ID: 1512029
2. Name: Trần Quốc Bảo
3. Emal: tranquocbao3897@gmail.com
4. Version Visual Studio: Community 2017 
5. Release: Bản release được build ở dạng release.
### -------------- HAVE DONE --------------
1. Giao diện chương trình. (Menu, Status Bar)
2. Xử lý GDI, Open File và Save File.
3. Bọc tất cả các đối tượng vẽ vào các lớp model. 
4. Sử dụng đa xạ (polymorphism) để cài đặt việc quản lý các đối tượng và vẽ hình. 
5. Sử dụng mẫu thiết kế prototypes để tạo ra hàng mẫu nhằm vẽ ở chế độ xem trước (preview).
6. Sử dụng mẫu thiết kế Factory để tạo mới đối tượng. 
7. Cụ thể:

> #GDI
1. Vẽ được các hình cơ bản: Line, Rectangle, Ellipse.
2. Xử lý nhấn Shift để vẽ Straight Line, Square, Circle.
3. Có khả năng Undo, Redo.

> #Open File và Save File
1. Mở và lưu được các định dạng binary (.objpaint), bitmap (.bmp), png (.png).
2. Ở định dạng binary có khả năng Undo, Redo - load lại phiên làm việc cũ.
3. Ở định dạng bitmap, png chỉ có khả năng load hình và vẽ đè lên.
4. Bitmap được xử lý bằng GDI. PNG được xử lý bằng GDI+.
(Vì chỉ có GDI+ mới hỗ trợ PNG)

> #GUI
1. Sử dụng các phím tắt để thao tác nhanh. (Bảng phím tắt ở dưới)
2. Status bar, hiển thị vị trí con trỏ chuột trên nền vẽ, hiển thị kích thước nền vẽ,
định dạng hình đang vẽ (Line - Straight line, Rectangle - Square, Ellipse - Circle)

> #Issues
1. Open file phải giữ hình liên tục được vẽ lại ở WM_PAINT.
Như vậy không được tối ưu hóa, đã xử dụng BitBlt để lưu HDC xuống Memory nhưng,
không load lên được.

### -------------- MAIN FLOW --------------
1. Khởi chạy chương trình, mặc định vẽ line, tùy chọn các hình vẽ cơ bản ở menu.
2. Vẽ trên nền chương trình.
3. Có thể Save file những thứ đã vẽ lại dưới các định dạng  binary (.objpaint), bitmap (.bmp), png (.png).
4. Có thể Open file để tiếp tục vẽ.
### ---------- ADDITIONAL FLOW ------------
1. Khi thoát chương trình, nếu đã vẽ mà chưa lưu sẽ hỏi có muốn lưu hay không?
2. Bắt các lỗi mở và lưu file.
### ------------ LINK BITBUCKET -----------
> 
```
Chú ý link repository trên là private đã add key public của giáo viên.
Đồng thời add user tdquang_edu vào repository với quyền read.
```
### ------------- LINK YOUTUBE ------------
> 