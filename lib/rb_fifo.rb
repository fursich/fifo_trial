class RBFifo
  attr_reader :length

  def initialize
    @length = 0
    @last_node = nil
    @first_node = nil
  end

  def enqueue(val)
    new_node = Node.new(val)

    if length.zero?
      @first_node = @last_node = new_node
    else
      @last_node.next = new_node
      @last_node      = new_node
    end
    @length += 1
    self
  end

  def dequeue
    return nil if length.zero?

    old_node    = @first_node
    @first_node = old_node.next
    @last_node  = nil if @first_node.nil?

    @length -= 1
    old_node&.value
  end

  def back
    @last_node&.value
  end

  def front
    @first_node&.value
  end

  class Node
    attr_reader :value
    attr_accessor :next
    def initialize(val)
      @value = val
    end
  end
end
