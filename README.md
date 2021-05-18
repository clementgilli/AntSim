# AntSim

## <br> **Description**

<br> This project is a collaboration between Clément Gilli and Tom Pleskoff. Our goal was to simulate the behaviour of different ant colonies, feeding their nest with sugar and fighting other colonies. We worked aproximatively 20 hours each one. 

<br />
  <img alt="ant.gif" src="./Images/ant.gif"/>



## <br> **Get AntSim**
#### <br> **Required libs and tools**
- cmake
- sfml 


#### <br> **Compilation**
```sh
cmake .
make
```

#### <br> **Launching ant colony**
```
./ant_sim [OPTION] ...
OPTION : -w   ->   add crossed walls which separates the grid in four areas
```

## <br> **Commands**

### <br> **Display sugar pheromones**
- `A` - Red
- `Z` - Green
- `E` - Blue
- `R` - Yellow

### <br> **Display nest pheromones**

- `Q` - Red
- `S` - Green
- `D` - Blue
- `F` - Yellow

### <br> **Add walls**

- `Click Mouse` - Click on the screen where you want to add a wall




## <br> **Code conventions**

### <br> **Docstrings**

`@confidence 0-4`
- 0: it doesn't work
- 1: it "works" with known bugs
- 2: it works but can't be tested
- 3: it works and has been tested
- 4/5: it works, it has been tested and it is so simple that there is no doubt about it

<br>
<br>
<h1 align="center">
<img align=center alt="ant.png" src="./Images/ant.png"/>
</h1>