# MyGame
  ## Flappy Bird
# Mô tả game
  <p> Là game Flappy Bird tương tự trên phiên bản quen thuộc đã từng một thời gian nổi lên như một hiện tượng và mang lại thành công cho tác giả.</p>
  <p> Cách chơi đơn giản, sử dụng phím "Space" để nhảy, các phím điều hướng để chọn Menu.</p>
# Quá trình phát triển 
  ## Git tham khảo "https://github.com/Ducanger/Flappy-Doge-SDL2"
  ## Chức năng của các phần trong source code
    - background.cpp và background.h: hình thành nền cho game, lặp lại liên tục hình nền trong thời gian game hoặt động.
    - backup.cpp: fill màu nền trước khi có background.
    - base.h và base.cpp: đây là phần giới hạn khung hình bay của chim ở phía dưới
    - bird.h và bird.cpp: lấy hình ảnh chim trong folder "sprites\bird" (có 3 trạng thái của chim), các trạng thái được 
    tùy chỉnh theo hành động bay của chim và cả phần chọn menu
    - coin.h và coin.cpp: lấy hình ảnh tiền xu trong file "sprites\coin.png", tạo hình động cho xu với 3 trạng thái trong ảnh 
    - flappy_bird.h và flappy_bird.cpp: đây là phần chính để điều chỉnh hành động của chim theo các nút bấm trên bàn phím (không 
    có tương tác với chuột)
    - flash.h và flash.cpp: tạo hiệu ứng flash khi gameover
    - medal.h và medal.cpp: huy chương cho phần scoreboard sau khi gameover tùy các mức điểm sẽ có huy chương khác nhau, trong 
    file "sprites\medal.png".
    - message.h và message.cpp: tạo phần tiêu đề ở đầu game và bảng khung scoreboard
    - music.h và music.cpp: âm thanh và các hiệu ứng âm thanh khi có tác động qua bàn phím và trạng thái của chim 
    - newhs.h và newhs.cpp: khi có kỉ lục mới, tạo hình "sprites\new.png
    - pipe.h và pipe.cpp: tạo các ống trên màn hình, thiết lập giới hạn đường chim được bay qua
    - scoreboard.h và scoreboard.cpp: in hình số điểm trên nền scoreboard vừa tạo ra, bằng cách sử dụng hình các số trong file
    "sprites\scoresheet.png"
    - selection.h và selection.cpp: điều hình hình chim trong phần chọn main menu
    - text.h và text.cpp: hiện tùy chọn ở main menu
  ## Hình ảnh và âm thành được lấy tại "https://github.com/samuelcust/flappy-bird-assets"
