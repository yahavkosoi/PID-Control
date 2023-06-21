
# PID controller

PID controller for Arduino


## Functions

#### initialization

```
  pidControl myPidController(inR1, inR2, enR, inL1, inL2, enL);
```

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `inR1` | `int` | **Required**. input pin right motor 1|

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `inR2` | `int` | **Required**. input pin right motor 2|

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `enR` | `int` | **Required**. enable pin right motor|

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `inL1` | `int` | **Required**. input pin left motor 1|

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `inL2` | `int` | **Required**. input pin left motor 2|

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `enL` | `int` | **Required**. enable pin left motor|

#### turn to angle

```
  myPidController.goToAngle(deg, speed, Kp, Ki, Kd);
```
| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `deg` | `int` | **Required**. turning angle|

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `speed` | `int` | **Required**. speed of turn|

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `Kp` | `double` | **Required**. propotional gain|

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `Ki` | `double` | **Required**. integral gain|

| Parameter | Type     | Description                |
| :-------- | :------- | :------------------------- |
| `Kd` | `double` | **Required**. derivative gain|

## Authors

- [@yahavkosoi](https://www.github.com/yahavkosoi)

