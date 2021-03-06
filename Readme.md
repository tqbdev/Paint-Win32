# Paint Win32 Update GDI+ and Ribbon

### ---------------- INFO ----------------
1. Name: Trần Quốc Bảo
2. Emal: tranquocbao3897@gmail.com
3. Version Visual Studio: Community 2017 
4. Release: Bản release được build ở dạng release.

### -------------- HAVE DONE --------------
1. Giao diện chương trình. (Menu, Status Bar, Ribbon)
2. Xử lý GDI+, Open File và Save File.
3. Bọc tất cả các đối tượng vẽ vào các lớp model. 
4. Sử dụng đa xạ (polymorphism) để cài đặt việc quản lý các đối tượng và vẽ hình. 
5. Sử dụng mẫu thiết kế Prototypes để tạo ra hàng mẫu nhằm vẽ ở chế độ xem trước (preview).
6. Sử dụng mẫu thiết kế Factory để tạo mới đối tượng.
7. Cụ thể:

> #GDI+
1. Vẽ được các hình cơ bản: Line, Rectangle, Ellipse.
2. Xử lý nhấn Shift để vẽ Straight Line, Square, Circle.
3. Có khả năng Undo, Redo.
4. Khử răng cưa. (Anti Aliasing - AA)

> #Open File và Save File
1. Mở và lưu được các định dạng binary (.objpaint), bitmap (.bmp), png (.png).
2. Ở định dạng binary có khả năng Undo, Redo - load lại phiên làm việc cũ.
3. Ở định dạng bitmap, png chỉ có khả năng load hình và vẽ đè lên.
4. Bitmap, PNG được xử lý bằng GDI và GDI+.

> #GUI
1. Sử dụng các phím tắt để thao tác nhanh. (Bảng phím tắt ở dưới)
2. Status bar, hiển thị vị trí con trỏ chuột trên nền vẽ, hiển thị kích thước nền vẽ,
định dạng hình đang vẽ (Line - Straight line, Rectangle - Square, Ellipse - Circle)

> # Solve Issues
1. Sử dụng BitBlt để giảm giật hình khi vẽ lại. Hiện tại thì tỉ lệ giật rất thấp. (hầu như là không có)
Nhưng load PNG lên vẫn có lúc giật.
Sử dụng kỹ thuật Double-buffing - các biến sử dụng thường xuyên được đặt static để xử lý nhanh.

### --------- CHANGE LOG ver 3.0 ----------
1. Thay đổi hoàn toàn sang GDI+.
2. Thêm các tính năng như chọn màu vẽ, kiểu nét vẽ, độ to của nét vẽ.
3. Thêm tính năng đổ màu (Fill Color).
4. Thêm giao diện Ribbon. Giúp giao diện nhìn đẹp, dễ thao tác và sử dụng.
5. Thay đổi một số kỹ thuật nên không còn giật lag hình. (0%)
6. Sửa đổi cải tiến Undo-Redo.
7. Khử răng cưa. (Anti Aliasing - AA)

### -------------- MAIN FLOW --------------
1. Khởi chạy chương trình, mặc định vẽ line, tùy chọn các hình vẽ cơ bản ở menu.
2. Tùy chỉnh màu, nét vẽ theo sở thích, ý muốn.
3. Vẽ trên nền chương trình.
4. Nhấn shift vẽ các đối tượng đặc biệt (đường thẳng, hình vuông, hình tròn).
5. Có thể Save file những thứ đã vẽ lại dưới các định dạng  binary (.objpaint), bitmap (.bmp), png (.png).
6. Có thể Open file để tiếp tục vẽ.

### ---------- ADDITIONAL FLOW ------------
1. Khi thoát chương trình, nếu đã vẽ mà chưa lưu sẽ hỏi có muốn lưu hay không?
2. Khi mở file trong khi đang vẽ thì hỏi có muốn lưu hay không?

### ------- GIT ORGINAL (BITBUCKET) -------
> https://1512029@bitbucket.org/1512029/paint.git

### ------------- LINK YOUTUBE ------------
1. ver 1.0: https://youtu.be/Jk_jeQDzUdc
2. ver 2.0: https://youtu.be/Gz5Pj7eGp3Q
3. ver 3.0: https://youtu.be/gONk4k_3V6E