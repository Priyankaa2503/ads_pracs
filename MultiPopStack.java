import java.util.EmptyStackException;
import java.util.Stack;

public class MultiPopStack<T> {
    private Stack<T> stack;

    public MultiPopStack() {
        stack = new Stack<>();
    }

    public void push(T value) {
        System.out.println("Pushing " + value + " to stack.");
        stack.push(value);
    }

    public T pop() {
        if (isEmpty()) {
            throw new EmptyStackException();
        }
        return stack.pop();
    }

    public void multiPop(int n) {
        if (n > size()) {
            throw new IllegalArgumentException(
                    "Cannot pop " + n + " elements. Stack has only " + size() + " elements.");
        }
        
        if (n < 0) {
            throw new IllegalArgumentException("Cannot pop " + n + " elements.");
        }

        for (int i = 0; i < n; i++) {
            System.out.println("Popping " + stack.peek() + " from stack.");
            pop();
        }
    }

    public boolean isEmpty() {
        return stack.isEmpty();
    }

    public int size() {
        return stack.size();
    }

    public static void main(String[] args) {
        MultiPopStack<Integer> stack = new MultiPopStack<>();

        stack.push(10);
        stack.push(20);
        stack.push(30);
        stack.push(40);

        stack.multiPop(2);

        stack.push(50);
        stack.push(60);

        stack.multiPop(3);

        if (stack.isEmpty()) {
            System.out.println("Stack is empty.");
        } else {
            System.out.println("Stack size: " + stack.size());
        }
    }
}