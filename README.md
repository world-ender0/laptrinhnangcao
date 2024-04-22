# laptrinhnangcao
Họ và tên: Phạm Quang Hưng
MSSV: 23020084
Chủ đề game: Game rắn săn mồi. Đầu game spawn 3 quả táo. Táo vàng tăng score, tăng kích thước. Táo đỏ không tăng score, giảm kích thước (kích thước tối thiểu là 2). Ăn táo sẽ spawn ra 1 ô gạch ngẫu nhiên
Mô tả: Tạo lưới trên cửa sổ game chia ra thành m x n ô vuông, mỗi ô có tọa độ x= 1, 2, 3,... n và y = 1, 2, 3,... m. Một ô vuông sẽ ở 1 trong các trạng thái: empty (rỗng), food (quả táo), head (đầu rắn), body (thân rắn), hoặc wall (tường). Khi đầu rắn chạm vào thân hoặc chạm vào tường thì trò chơi kết thúc, tự động quay trở lại menu. Khi rắn di chuyển sẽ sử dụng 2 loại tọa độ: Tọa độ thực (pos) và tọa độ nguyên(new) (Để hiển thị ra trên màn hình vì các ô có tọa độ nguyên). Khi rắn đi đến ô [pos +1] thì new chuyển sang ô mới. Khi đó vẽ ra màn hình rắn đã di chuyển sang ô khác.
Render rắn: dùng 4 hình ảnh Head, Body1, Body2, Body3, Tail; và sẽ render rắn theo từng khúc (từng ô).  Body1 và Body2 là 2 đoạn uốn của rắn, Body3 là đoạn gấp khúc, ta sẽ flip các ảnh này tùy thuộc vào trường hợp di chuyển của rắn 
Ngưỡng điểm tự đánh giá: 7.5
[https://www.youtube.com/watch?v=HaG_cHeEmZ4](https://youtu.be/k3UbMZgX9M4)
