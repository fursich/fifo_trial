class RBLifo
  attr_reader :length, :last

  def initialize
    @length = 0
    @last = nil
  end

  def push(val)
    @last = Element.new(val, last) 
    @length += 1
    self
  end

  def pop
    return nil if length.zero?

    last_object = last
    @last = last_object.parent
    @length -= 1
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
