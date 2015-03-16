#Architecture proposal for WhiteAnt kernel

# Introduction #

The architecture is divided as UI and kernel. Each part should be taken care individually.
This page will discuss kernel part.

# Details #

![http://nglogviewer.googlecode.com/files/WhiteAntKernelArchi.png](http://nglogviewer.googlecode.com/files/WhiteAntKernelArchi.png)

As you can see above, the architecture could be divided as UI and Kernel. For this page, we address the kernel part. In the following sections, we will give explanation for each component.

## 1. UI ##
It provides easy-to-use interface for a user. The target for this layer is to show data as soon as possible. We will give another wiki page to describe the architecture.

## 2. LogFileWrapper ##
This is our kernel part. It represents a system layer, and provides high-level APIs for UI to access. In LogFileWrapper, it consists DecorationFactory, FilterFactory and FileProxy. We will describe each component later. Hereby, we introduce the interaction between each component.

### (1) How it works ###
When UI sets the filter items, LogFileWrapper will directly set the data into FilterFactory. Once the FilterFactory had processed the data, it will notify DecorationFactory to retrieve the latest data, and assign each data with appropriated color or bookmark tag. DecoractionFactory may callback to UI, so that UI could retrieve the latest information later.


## 3. FileProxy ##
It is a delegation of real file. Initially, we will preprocess a file to gain enough information, such as **the mapping between the n-th line and its file position**. It also maintains a **ring buffer**, storing the cached data from file. Note that we have to preprocess the data as **fast** as possible.

## 4. FilterFactory ##
When LogFileWrapper gives a new dictionary. It will enumerate each line from FileProxy and check the filter out those uninterested (maybe a good algorithm may help). Once it is done, it will notify DecorationFactory.

## 5. DecorationFactory ##
It will query data from FilterFactory and decorated them with specified color or bookmark tag. It also notifies UI once this operation done.

## 6. Real File ##
It represents a real file stored in the disk.