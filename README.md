# SignalSlot  
  Pure C++ code to implement signal & slot without using Qt's precompiled mechanism.  
  
In programming, when we change the status, we often want another part to be notified. More generally, we want objects of any kind to be able to communicate with one another. For example, if the temperature rises to a certain point, we may want to trigger an alarm.  
  
We don't use callback techniques; instead, we employ the mechanism of signals and slots. Signals are emitted when specific events occur, and slots are functions that respond to particular signals.  
  
The signature of a signal must match the signature of the receiving slot. Hence, the compiler can assist us in detecting type mismatches when using function-pointer-based syntax. Signals and slots are loosely coupled: the class emitting a signal neither knows nor cares about which slots receive the signal. The signal-slot mechanism ensures that if a signal is connected to a slot, the slot will be invoked with the correct timing using the parameters of the signal. Signals and slots can accommodate any number and type of parameters.  
  
Slots can be used for receiving signals, but they are also normal member functions. Just as an object does not know if anything receives its signals, a slot does not know if it has any signals connected to it. This ensures that truly independent components can be created.  
  
You can connect any number of signals to a single slot, and signals can be connected to any number of slots.  
![image](https://github.com/kachuu/SignalSlot/blob/main/abstract-connections.png)  
  
Redirecting a signal to another slot.  
![image](https://github.com/kachuu/SignalSlot/blob/main/SignalSlot.jpg)  
  
Connect signals to slots using the 'connect' macro.  
'signal_member' is a member within 'senderObj'  
'receiverClass::slot_function' is the definition of a class member function within 'receiverObj'  
```bash  
connect(senderObj, signal_member, receiverObj, receiverClass::slot_function);  
```  
  
Disconnect signals to slots using the 'disconnect' macro.  
'signal_member' is a member within 'senderObj'  
```bash  
disconnect(senderObj, signal_member, receiverObj);  
```  
  