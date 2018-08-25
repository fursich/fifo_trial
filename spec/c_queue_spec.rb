require 'spec_helper'
require_relative '../bin/fifo.bundle'

RSpec.describe 'FIFO (c ext)' do
  it_behaves_like 'queue' do
    let(:base_queue) { Fifo.new }
  end
end
