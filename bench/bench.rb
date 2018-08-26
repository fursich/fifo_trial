require 'benchmark'
require_relative '../bin/lifo.bundle'
require_relative '../bin/fifo.bundle'
require_relative '../lib/rb_lifo.rb'
require_relative '../lib/rb_fifo.rb'
require_relative '../bin/clifo.bundle'

BENCHMARK_COUNT = 100
UNIT_ITERATION = 100000

Benchmark.bm BENCHMARK_COUNT do |r|  
  r.report 'LIFO (c-ext)' do
    l = Lifo.new
    UNIT_ITERATION.times do |n|
      l.push(n)
    end
    UNIT_ITERATION.times do |n|
      l.pop
    end
  end

  r.report 'LIFO (ruby)' do
    l = RBLifo.new
    UNIT_ITERATION.times do |n|
      l.push(n)
    end
    UNIT_ITERATION.times do |n|
      l.pop
    end
  end

  r.report 'LIFO (using c struct)' do
    l = CLifo.new
    UNIT_ITERATION.times do |n|
      l.push(n)
    end
    UNIT_ITERATION.times do |n|
      l.pop
    end
  end

  r.report 'FIFO (c-ext)' do
    f = Fifo.new
    UNIT_ITERATION.times do |n|
      f.enqueue(n)
    end
    UNIT_ITERATION.times do |n|
      f.dequeue
    end
  end

  r.report 'FIFO (ruby)' do
    f = RBFifo.new
    UNIT_ITERATION.times do |n|
      f.enqueue(n)
    end
    UNIT_ITERATION.times do |n|
      f.dequeue
    end
  end

end

