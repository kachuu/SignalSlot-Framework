# SignalSlot Framework  
  Pure C++ code to implement signal & slot without using Qt's precompiled mechanism.  
  
In programming, when we change the status, we often want another part to be notified. More generally, we want objects of any kind to be able to communicate with one another.  
  
We don't use callback techniques; instead, we employ the mechanism of signals and slots. Signals are emitted when specific events occur, and slots are functions that respond to particular signals.  
  
The signature of a signal must match the signature of the receiving slot. Hence, the compiler can assist us in detecting type mismatches when using function-pointer-based syntax. Signals and slots are loosely coupled: the class emitting a signal neither knows nor cares about which slots receive the signal. The signal-slot mechanism ensures that if a signal is connected to a slot, the slot will be invoked with the correct timing using the parameters of the signal. Signals and slots can accommodate any number and type of parameters.  
  
Slots can be used for receiving signals, but they are also normal member functions. Just as an object does not know if anything receives its signals, a slot does not know if it has any signals connected to it. This ensures that truly independent components can be created.  
  
### How Signals and Slots Work  
The signal corresponds to multiple slots, with each slot being a reference to a receiver. When the signal is emitted, it will invoke each slot associated with this signal, and the invocation order of the slots depends on their position in the slot list. The later a slot is added, the later it will be called.  
![image](https://github.com/kachuu/SignalSlot/blob/main/SignalSlot1.jpg)  
  
### You can connect any number of signals to a single slot, and signals can be connected to any number of slots  
![image](https://github.com/kachuu/SignalSlot/blob/main/abstract-connections.png)  
  
### Redirecting a signal to another slot  
I've considered a mechanism similar to Qt's where one signal directly connects to another signal (whenever one signal is emitted, it immediately emits a second signal). However, I feel that such a mechanism isn't extremely important. It simply saves writing an extra function (possibly saving around 3 lines of code), and it's not very friendly for debugging since it's inconvenient to set breakpoints or output debug logs.  
![image](https://github.com/kachuu/SignalSlot/blob/main/SignalSlot.jpg)  
  
## Example  
### Connect signals to slots  
Create an object for signal that takes an int type parameter.  
```bash  
class Sender
{
public:
    TSignal<int> signal_1param;
};
```  
  
Create an object that receives signal, with a slot function that takes an integer parameter.  
```bash  
class Receiver
{
public:
    void slot_1param(int v) {
        //to do something
    }
};
```  
  
Use the *connect* macro to connect signal with slot.  
*Receiver::slot_1param* is the definition of a class member *void slot_1param(int v)* within *Receiver*  
```bash  
connect(Sender, signal_1param, Receiver, Receiver::slot_1param);
```  
  
### Send a signal  
Invoke the *signal_1param* object within the *Sender* object, and pass the required integer value (here using the integer 1000), thus triggering the signal handling.  
```bash  
sender->signal_1param(1000);
```  
  
### Disconnect signals to slots  
Use the *disconnect* macro to break the connection between signals and slots, similar to the method used in the *connect* macro.  
When the third parameter is *not zero*, only the connections between the signal and slots related to *Receiver* object are removed. Connections between other object signals and slots remain unaffected.  
```bash  
disconnect(Sender, signal_1param, Receiver);
```  
  
When the third parameter is *zero*, remove all connections of signals and slots associated with *Sender*.  
```bash  
disconnect(Sender, signal_member, 0);
```  
  
