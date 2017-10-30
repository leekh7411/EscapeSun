# EscapeSun
- 임베디드 소프트웨어 경진대회 2017 인텔코리아 부문 메인보드
- 인텔 큐리보드와 외부 센서를 활용한 온열 감지 키트
## LIBRARY
- Add your library in libraries folder
- change sketchbook location to ~/EscapeSun/main
- Write library in Main.ino
## 설명
- 연결된 체온, 외부 온도, 습도센서로 부터 데이터와 인텔 큐리보드의 가속도 센서등의 도움을 받아 위험 감지 알고리즘을 실행합니다. 
- 단계별 위험 스코어에 따라 예상되는 온열질환에 대한 조언을 합니다
- 의식이 없는 것으로 판단 될 경우 부저를 통해 의식 확인 절차를 거친 뒤 의식이 없다면 Android App을 통해 긴급 구조 요청 문자 메시지를 전송합니다.
- 긴급 구조 요청 문자 메시지에는 현재 착용자의 신체 정보, Android App을 통한 GPS기반 위치정보를 통해 환자의 골든 타임을 놓치지 않도록 도와주게 됩니다.
