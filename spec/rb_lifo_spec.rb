require 'spec_helper'
require_relative '../lib/rb_lifo.rb'

RSpec.describe 'LIFO (ruby)' do
  it_behaves_like 'stack' do
    let(:base_stack) { RBLifo.new }
  end
end
