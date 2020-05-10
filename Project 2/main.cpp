#include "Header.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;
bool Testcase (Header &task,string example){
    Header exampleHeader;
    string add="examples/";
    exampleHeader.LoadFile(add+example,exampleHeader);
    if(task.idLength!=exampleHeader.idLength){
        return false;
    }
    if(task.colorMapType!=exampleHeader.colorMapType){
        return false;
    }
    if(task.dataTypeCode!=exampleHeader.dataTypeCode){
        return false;
    }
    if(task.colorMapOrigin!=exampleHeader.colorMapOrigin){
        return false;
    }
    if(task.colorMapLength!=exampleHeader.colorMapLength){
        return false;
    }
    if(task.colorMapDepth!=exampleHeader.colorMapDepth){
        return false;
    }
    if(task.xOrigin!=exampleHeader.xOrigin){
        return false;
    }
    if(task.yOrigin!=exampleHeader.yOrigin){
        return false;
    }
    if(task.width!=exampleHeader.width){
        return false;
    }
    if(task.height!=exampleHeader.height){
        return false;
    }
    if(task.bitsPerPixel!=exampleHeader.bitsPerPixel){
        return false;
    }
    if(task.imageDescription!=exampleHeader.imageDescription){
        return false;
    }
    for(unsigned int i=0;i<task.height*task.width;i++){
        if(task.pixelVec[i].red!=exampleHeader.pixelVec[i].red){
            return false;
        }
        if(task.pixelVec[i].green!=exampleHeader.pixelVec[i].green){
            return false;
        }
        if(task.pixelVec[i].blue!=exampleHeader.pixelVec[i].blue){
            return false;
        }
        if(task.pixelVec[i].redValue!=exampleHeader.pixelVec[i].redValue){
            return false;
        }
        if(task.pixelVec[i].greenValue!=exampleHeader.pixelVec[i].greenValue){
            return false;
        }
        if(task.pixelVec[i].blueValue!=exampleHeader.pixelVec[i].blueValue){
            return false;
        }
    }
    return true;
}

int main() {

    Header layer1,text2,text,pattern2,pattern1,layer2,layer_red,layer_green,layer_blue,circles,car;
    layer1.LoadFile("input/layer1.tga",layer1);
    text2.LoadFile("input/text2.tga",text2);
    text.LoadFile("input/text.tga",text);
    pattern2.LoadFile("input/pattern2.tga",pattern2);
    pattern1.LoadFile("input/pattern1.tga",pattern1);
    layer2.LoadFile("input/layer2.tga",layer2);
    layer_red.LoadFile("input/layer_red.tga",layer_red);
    layer_blue.LoadFile("input/layer_blue.tga",layer_blue);
    layer_green.LoadFile("input/layer_green.tga",layer_green);
    circles.LoadFile("input/circles.tga",circles);
    car.LoadFile("input/car.tga",car);
    //Task 1
    Header task=layer1;
    task.pixelVec=task.Multiply(layer1,pattern1);
    task.WriteFile(task,task.pixelVec,"part1.tga");
    cout<<"Test #1...... ";
    if(Testcase(task,"EXAMPLE_part1.tga")){
        cout<<"Passed!"<<endl;
    }else{
        cout<<"Failed!"<<endl;
    }
    //Task 2
    Header task2=car;
    task2.pixelVec=task.Subtract(layer2,car);
    task.WriteFile(task2,task2.pixelVec,"part2.tga");
    cout<<"Test #2...... ";
    if(Testcase(task2,"EXAMPLE_part2.tga")){
        cout<<"Passed!"<<endl;
    }else{
        cout<<"Failed!"<<endl;
    }
    //Task 3
    Header temp=layer1;
    temp.pixelVec=task.Multiply(layer1,pattern2);
    task.pixelVec=task.Screen(temp,text);
    task.WriteFile(task,task.pixelVec,"part3.tga");
    cout<<"Test #3...... ";
    if(Testcase(task,"EXAMPLE_part3.tga")){
        cout<<"Passed!"<<endl;
    }else{
        cout<<"Failed!"<<endl;
    }
    //Task 4
    temp.pixelVec=task.Multiply(layer2,circles);
    task.pixelVec=task.Subtract(pattern2,temp);
    task.WriteFile(task,task.pixelVec,"part4.tga");
    cout<<"Test #4...... ";
    if(Testcase(task,"EXAMPLE_part4.tga")){
        cout<<"Passed!"<<endl;
    }else{
        cout<<"Failed!"<<endl;
    }
    //Task 5
    task.pixelVec=task.Overlay(layer1,pattern1);
    task.WriteFile(task,task.pixelVec,"part5.tga");
    cout<<"Test #5...... ";
    if(Testcase(task,"EXAMPLE_part5.tga")){
        cout<<"Passed!"<<endl;
    }else{
        cout<<"Failed!"<<endl;
    }
    //Task 6
    task.pixelVec=task.AddGreenChannel(car);
    task.WriteFile(task,task.pixelVec,"part6.tga");
    cout<<"Test #6...... ";
    if(Testcase(task,"EXAMPLE_part6.tga")){
        cout<<"Passed!"<<endl;
    }else{
        cout<<"Failed!"<<endl;
    }
    //Task 7
    task.pixelVec=task.Scale(car);
    task.WriteFile(task,task.pixelVec,"part7.tga");
    cout<<"Test #7...... ";
    if(Testcase(task,"EXAMPLE_part7.tga")){
        cout<<"Passed!"<<endl;
    }else{
        cout<<"Failed!"<<endl;
    }
    //Task 8
    Header taskr, taskg, taskb;
    taskr=car;
    taskr.pixelVec=task.WriteChannel(taskr,"red");
    task.WriteFile(taskr,taskr.pixelVec,"part8_r.tga");
    taskg=car;
    taskg.pixelVec=task.WriteChannel(taskg,"green");
    task.WriteFile(taskg,taskg.pixelVec,"part8_g.tga");
    taskb=car;
    taskb.pixelVec=task.WriteChannel(taskb,"blue");
    task.WriteFile(taskb,taskb.pixelVec,"part8_b.tga");
    cout<<"Test #8...... ";
    if(Testcase(taskr,"EXAMPLE_part8_r.tga")&&Testcase(taskg,"EXAMPLE_part8_g.tga")&&Testcase(taskb,"EXAMPLE_part8_b.tga")){
        cout<<"Passed!"<<endl;
    }else{
        cout<<"Failed!"<<endl;
    }
    //Task 9
    Header task9=layer_red;
    task9.pixelVec=task.CombineChannels(layer_red,layer_green,layer_blue);
    task.WriteFile(task9,task9.pixelVec,"part9.tga");
    cout<<"Test #9...... ";
    if(Testcase(task9,"EXAMPLE_part9.tga")){
        cout<<"Passed!"<<endl;
    }else{
        cout<<"Failed!"<<endl;
    }
    //Task 10
    Header lastTask=text2;
    lastTask.pixelVec=task.Rotate(text2);
    task.WriteFile(lastTask,lastTask.pixelVec,"part10.tga");
    cout<<"Test #10...... ";
    if(Testcase(lastTask,"EXAMPLE_part10.tga")){
        cout<<"Passed!"<<endl;
    }else{
        cout<<"Failed!"<<endl;
    }
    return 0;


}
