class RBLifo
  attr_reader :length

  def initialize
    @length = 0
    @last_node = nil
  end

  def push(val)
    @last_node = Node.new(val, @last_node) 
    @length += 1
    self
  end

  def pop
    return nil if length.zero?

    node = @last_node
    @last_node = node.parent
    @length -= 1
    node.value
  end

  def value
    @last_node&.value
  end

  class Node
    attr_reader :value, :parent
    def initialize(val, parent)
      @value = val
      @parent = parent
    end
  end
end
