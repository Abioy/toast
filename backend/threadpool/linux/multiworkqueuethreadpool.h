/*
 * Copyright (C) 2007-2013 Alibaba Group Holding Limited
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef MULTIWORDQUEUETHREADPOOL_H
#define MULTIWORDQUEUETHREADPOOL_H
#include "workerthread.h"
#include <vector>
// ��ThreadPool �е� ÿ��Thread ����Ӧһ���������У����߳�
// ֻ����ù��������е������ⲿ����ָ�����͵��Ǹ�����������(
// ����ţ�����̳߳�һ���������̸߳�����̶������߳�ִ�й�����
// �����޸�
class MultiWorkQueueThreadPool
{
public:
    static MultiWorkQueueThreadPool * Create(uint_t num_threads, pthread_attr_t *attr);
    int AddWork(uint_t index, void *(*func)(void *), void *arg);
    static void Destroy(MultiWorkQueueThreadPool * pool, int timeout_sec);
    void PoolWait(int timeout_sec);
    uint_t GetThreadNumber()
    {
        return m_num_threads;
    }
private:
    MultiWorkQueueThreadPool(uint_t num_threads, pthread_attr_t *attr);
    ~MultiWorkQueueThreadPool();
private:
    std::vector<WorkerThread*> m_threads;
    uint_t       m_num_threads;
};
#endif
