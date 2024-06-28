# Micro Gravity Experimental kit

An Open-Source Platform for Accessible Space Science Experiments.

![](https://github.com/MouraWM/MGX-micro-gravity-experimental-kit/images/wd.jpg)

![](https://img.shields.io/github/stars/MouraWM/MGX-micro-gravity-experimental-kit) ![](https://img.shields.io/github/forks/MouraWM/MGX-micro-gravity-experimental-kit.svg) ![](https://img.shields.io/github/release/MouraWM/MGX-micro-gravity-experimental-kit.svg) ![](https://img.shields.io/github/issues/MouraWM/MGX-micro-gravity-experimental-kit.svg) ![](https://img.shields.io/github/bower/MouraWM/MGX-micro-gravity-experimental-kit.svg)

## Features

This work aims to develop the Micro Gravity Experimental kit (MGX), a multipurpose experimental platform that can serve various experimental purposes. A highly active area in micro gravity research is biological investigations and measurements. For instance, analyzing biological images in micro gravity is important to understanding the effects of this environment on living organisms. Therefore, having a platform that allows for the development of an automated system to capture, process, and analyze biological images in real-time during micro gravity experiments would be an example of what the proposed system in this work could achieve. This system would not be limited to this application but could also serve as an instrument for research in other fields such as ionospheric physics, materials science, and space technologies. 



## Architecture

In MGX Architecture, the expected output is a representation in a lower level of abstraction, such as a block diagram, lowering the abstraction level of the MGX module facilitated the test and validation of the module requirement by incremental integration. Furthermore, NASA 8739.23A declares that an architecture review based on the block diagram could ensure that all the requirements have been addressed. Likewise, DO-254 states that using a functional block diagram as a high-level design concept helps to assess the potential for the resulting design implementation to meet the requirements.
Figure 1 represents the MGX internal architecture, where the main controller (Jetson Orin Nano) connects to the 14 main parts of the MGX. Thus, a picture of what is contained inside the MGX can be observed, and any deviation from the initial project can be corrected.

![](https://github.com/MouraWM/MGX-micro-gravity-experimental-kit/blob/main/images/Fig01.png)

> Figure 1. MGX architecture



## Hardware Design Detail

More detailed hardware can be developed based on the architecture presented in Figure 1. A printed circuit board can be developed from the detailed hardware, providing ways to build a physical model of the MGX. Each of the MGX's 14 features is intended to provide the kit's user with ways to implement its own experiments. Temperature, pressure, and IMU are common measures used in microgravity missions. Thus, they are integrated parts of the MGX. However, if another phenomenon needs to be measured, the MGX offers other ways to connect with the desired sensor. For example, an accelerometer of different ranges provided by MGX is needed. It can be connected through the I2C or SPI bus, or if the output is analog, it can be connected to one of the 32 analog channels. Such flexibility gives freedom to the user to deploy a variety of experiments.
If the payload is recovered, the M2 NVMe bus can be connected to an SSD data storage that can be used to store the experiment data; however, if there is no recovery or the recovery fails, it is possible to use the serial channel connected to a PCM and transmitter to send the data over the telemetry channel. 

How some experiments have cameras to observe their behavior, the MGX offers two camera connections to observe different angles of the experiment or even different experiments. The Jetson board offers connections up to 4K resolution at 30 fps.  This configuration delivers a good-quality image, allowing the user to study the micro gravity phenomenon more clearly. Moreover, some experiments used in micro gravity need actuators. The MGX offers a dedicated 4 Ampere current output to provide such a feature. Some experiments will need an oven or a cooler, and such experiments demand high currents to operate properly.

The UARTs are intended to communicate with other experiments, or to communicate with the MGX to configure it. However, the signal can be degraded when not properly referenced (grounded). To avoid this problem, the MGX could benefit from commercial integrated circuits to easily the task of isolation. For example, the integrated circuit MAX33250E can be used. Thus, it provides an isolated UART 1 that complies with the RS-232 standard. Figure 2 shows the implementation of the MAX33250E inside the MGX. 

![](https://github.com/MouraWM/MGX-micro-gravity-experimental-kit/blob/main/images/Fig02.png)

> Figure 2. Detailed implementation of the Isolated UART RS-232



## Software Implementation and Functionality

(.......)
