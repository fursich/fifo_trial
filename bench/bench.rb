require 'benchmark'
require_relative '../lib/fifo.bundle'
require_relative '../lib/rb_fifo.rb'

BENCHMARK_COUNT = 100
UNIT_ITERATION = 100000

Benchmark.bm BENCHMARK_COUNT do |r|  
  r.report 'FIFO (c-ext)' do
    f = Fifo.new
    UNIT_ITERATION.times do |n|
      f.push(n)
    end
    UNIT_ITERATION.times do |n|
      f.pop
    end
  end

  r.report 'FIFO (ruby)' do
    f = RBFifo.new
    UNIT_ITERATION.times do |n|
      f.push(n)
    end
    UNIT_ITERATION.times do |n|
      f.pop
    end
  end
end

