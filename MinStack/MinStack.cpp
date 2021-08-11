class MinStack {
private:
    class SimpleStack {
    public:
        /** initialize your data structure here. */
        SimpleStack() {
            m_size = 0;
            m_cap = 400;
            m_data = new int[m_cap];
        }
        ~SimpleStack() {
            delete[] m_data;
        }

        void push(int val) {
            if (m_size == m_cap)
            {
                ResizeArr();
            }
            m_data[m_size++] = val;
        }

        void pop() {
            --m_size;
        }

        int top() {
            return m_data[m_size - 1];
        }

        void ResizeArr()
        {
            m_cap *= 2;
            int* arr2 = new int[m_cap];
            for (int i = 0; i < m_size; ++i)
            {
                arr2[i] = m_data[i];
            }
            for (int i = m_size; i < m_cap; ++i)
            {
                arr2[i] = 0;
            }
            delete[] m_data;
            m_data = nullptr;
            m_data = arr2;
            arr2 = nullptr;
        }

    private:
        int* m_data;
        int m_size;
        int m_cap;
    };
public:

    MinStack() {
        m_size = 0;
        m_cap = 200;
        m_data = new int[m_cap];
    }
    ~MinStack() {
        delete[] m_data;
    }

    void push(int val) {
        if (!m_size)
        {
            m_minStack.push(val);
        }
        else
        {
            if (m_minStack.top() >= val)
            {
                m_minStack.push(val);
            }
        }
        if (m_size == m_cap)
        {
            ResizeArr();
        }
        m_data[m_size++] = val;
    }

    void pop() {
        if (m_minStack.top() == m_data[m_size - 1])
        {
            m_minStack.pop();
        }
        --m_size;
    }

    int top() {
        return m_data[m_size - 1];
    }

    int getMin() {
        return  m_minStack.top();
    }

    void ResizeArr()
    {
        m_cap *= 2;
        int* arr2 = new int[m_cap];
        for (int i = 0; i < m_size; ++i)
        {
            arr2[i] = m_data[i];
        }
        for (int i = m_size; i < m_cap; ++i)
        {
            arr2[i] = 0;
        }
        delete[] m_data;
        m_data = nullptr;
        m_data = arr2;
        arr2 = nullptr;
    }

private:
    int* m_data;
    int m_size;
    int m_cap;
    SimpleStack m_minStack{};
};
