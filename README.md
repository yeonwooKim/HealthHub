# HealthHub
Projects done while working in HealthHub

### Sample Image Viewer를 돌리는 방법

* 먼저 [Google Native Client 공식 홈페이지](https://developer.chrome.com/native-client/sdk/download) 에서 Native Client SDK를 다운로드 받으세요.
* nacl\_sdk 디렉토리에 들어가서 naclsdk update 명령어를 입력하세요.
* pepper\_(최신 버전)/examples 디렉토리를 지우세요.
* 지운 디렉토리를 새로 만들고 그 안에 이 저장소를 clone 하세요.
* make serve 명령어를 입력하세요.
* [여기](localhost:5103/api/1.fileIO_urlLoader)로 접속하면 볼 수 있어요.
* 여러 기능에 대한 설명은 clone된 디렉토리안의 TODO를 참조하세요.
* 자세한 기능들의 구현순서와 Trouble shooting은 commit message를 참조하세요.
