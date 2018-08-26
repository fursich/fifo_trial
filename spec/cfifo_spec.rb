require 'spec_helper'
require_relative '../bin/cfifo.bundle'

RSpec.describe 'FIFO (usng c struct)' do
  it_behaves_like 'queue' do
    let(:base_queue) { CFifo.new }
  end
end
