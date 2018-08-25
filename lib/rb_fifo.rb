class RBFifo
  attr_reader :depth, :last

  def initialize
    @depth = 0
    @last = nil
  end

  def push(val)
    @last = Element.new(val, last) 
    @depth += 1
    self
  end

  def pop
    return nil if depth.zero?

    last_object = last
    @last = last_object.parent
    @depth -= 1
    last_object.value
  end

  def value
    last&.value
  end

  class Element
    attr_reader :value, :parent
    def initialize(val, parent)
      @value = val
      @parent = parent
    end
  end
end
