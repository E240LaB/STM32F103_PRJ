2020/07/29
1. 將User資料夾中的EXTI_interupt.c加入USER的裡面
(左側project->USER->右鍵->Add Existing Files to Group 'USER'->EXTI_interupt.c)

2. 原本在USER_UI中的檔案，複製到HARDWARE中，並將在USER_UI中的檔案移除
(左側project->HARDWARE->Add Existing Files to Group 'HARDWARE'->controllow,input,output,test_func)
(左側project->USER_UI->controllow,input,output,test_func的右鍵->remove File 'controllow,input,output,test_func')

已解決的問題
1.USB拔掉後，可以正常執行程式

待解決
1.MPU6050(註解掉 尚未測)

======================================================================================================================